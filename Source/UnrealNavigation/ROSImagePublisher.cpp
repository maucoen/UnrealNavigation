// Fill out your copyright notice in the Description page of Project Settings.

#include "ROSImagePublisher.h"
#include "TimerManager.h"
#include "CaptureManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
AROSImagePublisher::AROSImagePublisher(const FObjectInitializer &ObjectInitializer)
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryActorTick.bCanEverTick = true;

    // All socket and timers defined in .h, editable in editor.
}

// Called when the game starts
void AROSImagePublisher::BeginPlay()
{
    Super::BeginPlay();

    auto Controller = UGameplayStatics::GetPlayerController(this, 0);
    if (Controller)
    {
        InputComponent = NewObject<UInputComponent>(this);
        if (InputComponent)
        {
            InputComponent->BindKey(EKeys::K, EInputEvent::IE_Pressed, this, &AROSImagePublisher::TogglePublish);
            EnableInput(Controller);
        }
    }

    if (bIsCompressed)
    {
        Type = TEXT("sensor_msgs/CompressedImage");
    }
    else
    {
        Type = TEXT("sensor_msgs/Image");
    }

    //handles imaging types and ROS connection
    SetupImager();
}

// Called when game ends or actor deleted
void AROSImagePublisher::EndPlay(const EEndPlayReason::Type Reason)
{
    LastFrame.Empty();

    if (Handler.IsValid())
        Handler->Disconnect();

    Super::EndPlay(Reason);
}

// Called every frame
void AROSImagePublisher::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("tick"));
    while (!LastFrame.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("non empty"));
        //FGTCaptureTask Task;
        //PendingTasksROS.Peek(Task);

        uint64 FrameToRender;
        LastFrame.Peek(FrameToRender);
        uint64 CurrentFrame = GFrameCounter;
        int WaitCount = 1;

        //frametorender needs one or 2 ticks before it's rendered, we skip tick otherwise
        if (CurrentFrame > (FrameToRender + WaitCount))
        {
            LastFrame.Pop();

            UE_LOG(LogTemp, Warning, TEXT("inside framer"));
            for (int i = 0; i < Modes.Num(); i++)
            {
                if (i > 0 && (ImagingType == EImagingType::STEREO)) //stereo eye
                {
                    GTCapturers[i]->SetRelativeLocation(StereoBaselineCm);
                }
                //check for capture component directly
                if (GTCapturers[i]->GetCaptureComponent(Modes[i]) != nullptr)
                {
                    TArray<uint8> ImgData;
                    if (bIsCompressed)
                    {
                        ImgData = GTCapturers[i]->CapturePng(Modes[i]);
                    }
                    else
                    {
                        ImgData = GTCapturers[i]->CaptureNpyUint8(Modes[i], channels);
                        UE_LOG(LogTemp, Warning, TEXT("Capturing %s"), *Modes[i]);
                    }
                    ROSHeader.SetSeq(Count);
                    ROSHeader.SetStamp(FROSTime());

                    if (bSaveToDisk) //saves
                    {
                        FString Filename = FString::FromInt(Count++) + Modes[i] + FString::FromInt(i) + TEXT(".png");
                        GTCapturers[i]->SavePng(GTCapturers[i]->GetCaptureComponent(Modes[i])->TextureTarget, Filename);
                    }

                    if (Handler.IsValid())
                    {
                        // Send to ROS asynchronously!
                        (new FAutoDeleteAsyncTask<FSendToROS>(
                             Handler,
                             ImgData,
                             ROSHeader,
                             Topics[i],
                             bIsCompressed))
                            ->StartBackgroundTask();
                    }
                    else
                    {
                        UE_LOG(LogTemp, Warning, TEXT("NULL ROSBridge! No image sent"));
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("NULL Capture! No image sent"));
                }
            }
        }
        else {break; }
    }
}

void AROSImagePublisher::SetupImager()
{

    auto CastedPawn = Cast<APawn, AActor>(GetAttachParentActor());
    // Setup Correct types of capture Mode and ORBSLAM ROS Topic
    switch (ImagingType)
    {
        case EImagingType::MONO:
        {
            Modes.Add(TEXT("lit"));
            Topics.Add(TEXT("/camera/image_raw"));
            GTCapturers.Add(UGTCaptureComponent::Create(CastedPawn, Modes));
            break;
        }

        case EImagingType::RGBD:
        {
            Modes.Add(TEXT("lit"));
            Modes.Add(TEXT("vis_depth"));
            GTCapturers.Add(UGTCaptureComponent::Create(CastedPawn, Modes));
            GTCapturers.Add(UGTCaptureComponent::Create(CastedPawn, Modes));
            Topics.Add(TEXT("/camera/rgb/image_raw"));
            Topics.Add(TEXT("/camera/depth_registered/image_raw"));
            break;
        }

        case EImagingType::STEREO:
        {
            Modes.Add(TEXT("lit"));
            Modes.Add(TEXT("lit"));
            GTCapturers.Add(UGTCaptureComponent::Create(CastedPawn, Modes));
            GTCapturers.Add(UGTCaptureComponent::Create(CastedPawn, Modes));
            Topics.Add(TEXT("/camera/left/image_raw"));
            Topics.Add(TEXT("/camera/right/image_raw"));
            break;
        }
    }

    Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(IPAddress, Port));

    // Set websocket server address to default
    for (int i = 0; i < Modes.Num(); i++)
    {
        Handler->AddPublisher(
            MakeShareable<FROSBridgePublisher>(
                new FROSBridgePublisher(Topics[i], Type)));
    }

    Handler->Connect();
    UE_LOG(LogTemp, Warning, TEXT("handler on"));

    ROSHeader = std_msgs::Header(Count, FROSTime(), TEXT("0"));
}

void AROSImagePublisher::EnqueueImageTask()
{
    // FString InFilename = FString::FromInt(Count) + TEXT("mono.png");
    // FAsyncRecord* AsyncRecord = FAsyncRecord::Create();
    // FGTCaptureTask GTCaptureTask = FGTCaptureTask(Modes[0], InFilename, GFrameCounter, AsyncRecord);
    // PendingTasksROS.Enqueue(GTCaptureTask);

    LastFrame.Enqueue(GFrameCounter);
}

void AROSImagePublisher::TogglePublish()
{
    if (!bIsPublishing)
    {
        float Period = 1.0 / Frequency;

        GetWorldTimerManager().SetTimer(PublishTimer, this,
                                        &AROSImagePublisher::EnqueueImageTask, Period, true, 0.5f);

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1, 2.0f, FColor::Green, TEXT("starting image publishing"), true, FVector2D(2, 2));
        }
    }
    else
    {
        GetWorld()->GetTimerManager().ClearTimer(PublishTimer);
        
        LastFrame.Empty();

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1, 2.0f, FColor::Red, TEXT("stopping image publishing"), true, FVector2D(2, 2));
        }
    }

    bIsPublishing = !bIsPublishing;
}