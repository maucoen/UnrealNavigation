// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSImagePublisher.h"
#include "TimerManager.h"
#include "CaptureManager.h"

// Sets default values for this component's properties
UROSImagePublisher::UROSImagePublisher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    // All socket and timers defined in .h, editable in editor.
}

// Called when the game starts
void UROSImagePublisher::BeginPlay()
{
	Super::BeginPlay();

    Owner = GetOwner();
    CastedPawn = Cast<APawn>(Owner);

    
    // Set websocket server address to default
    Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(IPAddress, Port));

    if (bIsCompressed) {Type = TEXT("sensor_msgs/CompressedImage");}
    else { Type = TEXT("sensor_msgs/Image"); }

    // Setup Publisher to publish the correct types
    switch(ImagingType)
    {
        case EImagingType::MONO:
        {
            Modes.Add(TEXT("lit"));
            FString Topic = TEXT("/camera/image_raw");
            GTCapturer = UGTCaptureComponent::Create(CastedPawn, Modes);

        for (Topic : Topics)
            {
                Handler->AddPublisher(
		        MakeShareable<FROSBridgePublisher>(
                    new FROSBridgePublisher(Topic, Type)));
            }
            break;
        }

        case EImagingType::RGBD
        {
            Modes.Add(TEXT("lit"));
            Modes.Add(TEXT("depth")); 
            GTCapturer = UGTCaptureComponent::Create(CastedPawn, Modes);
            
            Topics.Add(TEXT("/camera/image_raw"));
            Topics.Add(TEXT("/camera/depth_registered/image_raw"));

            for (Topic : Topics)
            {
                Handler->AddPublisher(
		        MakeShareable<FROSBridgePublisher>(
                    new FROSBridgePublisher(Topic, Type)));
            }
            break;
        }

        case EImagingType::STEREO
        {
            Modes.Add(TEXT("lit"));
            GTCapturer = UGTCaptureComponent::Create(CastedPawn, Modes);
            
            Topics.Add(TEXT("/camera/left/image_raw"));
            Topics.Add(TEXT("/camera/right/image_raw"));

            for (Topic : Topics)
            {
                Handler->AddPublisher(
		        MakeShareable<FROSBridgePublisher>(
                    new FROSBridgePublisher(Topic, Type)));
            }
            break;
        }
    }

    ROSHeader = std_msgs::Header(Count, FROSTime(), TEXT("0"));

    //Connect to ROSBridge Websocket server.
    Handler->Connect();

    Owner->GetWorldTimerManager().SetTimer(GameStartTimer, this, 
	&UROSImagePublisher::EnqueueImageTask, Period, true, Delay);
}

// Called when game ends or actor deleted
void UROSImagePublisher::EndPlay(const EEndPlayReason::Type Reason)
{
    Super::EndPlay(Reason);
    Handler->Disconnect();   
}

// Called every frame
void UROSImagePublisher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (Count >= MaxImages)
    {
        GetWorld()->GetTimerManager().ClearTimer(GameStartTimer);
        UE_LOG(LogTemp, Warning, TEXT("stopped image pub"));
        PendingTasksROS.Empty();
        Count++;
    }

    while (!PendingTasksROS.IsEmpty())
	{
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
		USceneCaptureComponent2D* CaptureComponent = GTCapturer->GetCaptureComponent(Task.Mode);
		if (CaptureComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Unrecognized capture mode, in UROSImagePublisher Tick Component %s"), *Task.Mode);
		}
		else
		{
            // Capture Image
            TArray<uint8> ImgData;
            if (bIsCompressed)
            {
                ImgData = GTCapturer->CapturePng(Modes[0]);
                   
            }
            else 
            {
		        ImgData = GTCapturer->CaptureNpyUint8(Modes[0], channels);
            }
            ROSHeader.SetSeq(++Count);
		    ROSHeader.SetStamp(FROSTime());

            GTCapturer->SavePng(GTCapturer->GetCaptureComponent(Task.Mode)->TextureTarget,Task.Filename);
            // Send to ROS asynchronously!
            (new FAutoDeleteAsyncTask<FSendToROS>(
                Handler, 
                ImgData,
                ROSHeader,
                Topic,
                bIsCompressed
            ))->StartBackgroundTask();	
		}
		Task.AsyncRecord->bIsCompleted = true;
    }
    if(Handler.IsValid()) Handler->Process();
}

void UROSImagePublisher::EnqueueImageTask(ImagingType)
{

        // Setup Publisher to publish the correct types
    switch(ImagingType)
    {
        case EImagingType::MONO:
        {
            Modes.Add(TEXT("lit"));
            FString Topic = TEXT("/camera/image_raw");
            GTCapturer = UGTCaptureComponent::Create(CastedPawn, Modes);

            
	        Handler->AddPublisher(
		        MakeShareable<FROSBridgePublisher>(
                    new FROSBridgePublisher(Topic, Type)));
            break;
        }

        case EImagingType::RGBD
        {}
    }


    GTCapturer->SetWorldLocation(Owner->GetActorLocation()+FVector(0,0,150));
    // check(CaptureComponents.Num() != 0);
	USceneCaptureComponent2D* CaptureComponent = GTCapturer->GetCaptureComponent(Modes[0]);
	if (CaptureComponent == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Null pointer for capture component in enqueue ROS Task"));// return nullptr;

	const FRotator PawnViewRotation = CastedPawn->GetActorRotation();
	if (!PawnViewRotation.Equals(CaptureComponent->GetComponentRotation()))
	{
		CaptureComponent->SetWorldRotation(PawnViewRotation+FRotator(0,10,0));
	}
    FString InFilename = FString::FromInt(Count) + TEXT("test_async.png");
	FAsyncRecord* AsyncRecord = FAsyncRecord::Create();
	FGTCaptureTask GTCaptureTask = FGTCaptureTask(Modes[0], InFilename, GFrameCounter, AsyncRecord);
	PendingTasksROS.Enqueue(GTCaptureTask);
}