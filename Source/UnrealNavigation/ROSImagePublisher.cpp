// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSImagePublisher.h"
#include "TimerManager.h"
#include "CaptureManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
AROSImagePublisher::AROSImagePublisher(const FObjectInitializer& ObjectInitializer)
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
			InputComponent->BindKey(EKeys::K, EInputEvent::IE_Pressed, this, &AROSImagePublisher::StopPublish);
			EnableInput(Controller);
		}
	}

    auto CastedPawn = Cast<APawn, AActor>(GetAttachParentActor());

    if (bIsCompressed) {Type = TEXT("sensor_msgs/CompressedImage");}
    else { Type = TEXT("sensor_msgs/Image"); }

    // Setup Correct types of capture Mode and ORBSLAM ROS Topic
    switch(ImagingType)
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
    for (int i=0; i < Modes.Num(); i++)
    {
        Handler->AddPublisher(
		    MakeShareable<FROSBridgePublisher>(
                new FROSBridgePublisher(Topics[i], Type))); 
    }

    Handler->Connect();

    ROSHeader = std_msgs::Header(Count, FROSTime(), TEXT("0"));

    float Period = 1.0 / Frequency;

    GetWorldTimerManager().SetTimer(GameStartTimer, this, 
	&AROSImagePublisher::EnqueueImageTask, Period, true, Delay);
}

// Called when game ends or actor deleted
void AROSImagePublisher::EndPlay(const EEndPlayReason::Type Reason)
{
    PendingTasksROS.Empty();

    if (Handler.IsValid()) Handler->Disconnect(); 
    
    Super::EndPlay(Reason);
}

// Called every frame
void AROSImagePublisher::Tick(float DeltaTime)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    Super::Tick(DeltaTime);

    while (!PendingTasksROS.IsEmpty())
	{
        ++Count;
		FGTCaptureTask Task;
		PendingTasksROS.Peek(Task);
		uint64 CurrentFrame = GFrameCounter;

		int32 SkipFrame = 1;
		if (!(CurrentFrame > Task.CurrentFrame + SkipFrame)) // TODO: This is not an elegant solution, fix it later.
		{ // Wait for the rendering thread to catch up game thread.
            //UE_LOG(LogTemp, Warning, TEXT("Skipping a frame in Image Publisher tick component"));
			break;
		}  
        PendingTasksROS.Dequeue(Task);

        FVector eye = FVector(0,50,00);
        
        for (int i=0; i < Modes.Num(); i++)
        {
            if (i>0 && (Modes[i] == TEXT("lit"))) //stereo eye
            {
                GTCapturers[i]->SetRelativeLocation(eye);
            }           
		    USceneCaptureComponent2D* CaptureComponent = GTCapturers[i]->GetCaptureComponent(Modes[i]);
		            
             if (CaptureComponent == nullptr)
            {
                UE_LOG(LogTemp, Warning, TEXT("NULL Capture! No enqueue")); 
                return;
            }
		    else // Capture Image;
		    { 
                TArray<uint8> ImgData;
                if (bIsCompressed)
                {
                    ImgData = GTCapturers[i]->CapturePng(Modes[i]);
                }
                else 
                {
		            ImgData = GTCapturers[i]->CaptureNpyUint8(Modes[i], channels);
                    //UE_LOG(LogTemp, Warning, TEXT("Capturing %s"), *Modes[i]);
                }
                ROSHeader.SetSeq(Count);
		        ROSHeader.SetStamp(FROSTime());
    
                if (bSaveToDisk)
                { 
                    FString Filename = FString::FromInt(Count) + Modes[i]+ FString::FromInt(i)+ TEXT(".png");
                    GTCapturers[i]->SavePng(GTCapturers[i]->GetCaptureComponent(Modes[i])->TextureTarget,Filename);
                }

                if(Handler.IsValid())
                {
                    // Send to ROS asynchronously!
                    (new FAutoDeleteAsyncTask<FSendToROS>(
                        Handler, 
                        ImgData,
                        ROSHeader,
                        Topics[i],
                        bIsCompressed
                    ))->StartBackgroundTask();
                }  
            }       
		}
		Task.AsyncRecord->bIsCompleted = true;
    }  
}

void AROSImagePublisher::EnqueueImageTask()
{
    FString InFilename = FString::FromInt(Count) + TEXT("mono.png");
	FAsyncRecord* AsyncRecord = FAsyncRecord::Create();
	FGTCaptureTask GTCaptureTask = FGTCaptureTask(Modes[0], InFilename, GFrameCounter, AsyncRecord);
	PendingTasksROS.Enqueue(GTCaptureTask);
}

void AROSImagePublisher::StopPublish()
{
    GetWorld()->GetTimerManager().ClearTimer(GameStartTimer);
    UE_LOG(LogTemp, Warning, TEXT("stopped image pub"));
    PendingTasksROS.Empty();
}