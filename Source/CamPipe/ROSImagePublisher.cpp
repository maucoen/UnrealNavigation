// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSImagePublisher.h"
#include "TimerManager.h"
#include "ROSLoggerSimState.h"
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
    
    ROSHeader = std_msgs::Header(Count, FROSTime(), TEXT("0"));
    
    // Set websocket server address to default
    Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(IPAddress, Port));

    if (bIsCompressed) {Type = TEXT("sensor_msgs/CompressedImage");}
    else { Type = TEXT("sensor_msgs/Image"); }

    // **** Create publishers here ****
	Handler->AddPublisher(
		MakeShareable<FROSBridgePublisher>(
        new FROSBridgePublisher(Topic, Type)));

    //Connect to ROSBridge Websocket server.
    Handler->Connect();
    
    // Initialised Capture Components list 
    Owner = GetOwner();
    CastedPawn = Cast<APawn>(Owner);
    Modes.Add(TEXT("lit"));
    GTCapturer = UGTCaptureComponent::Create(CastedPawn, Modes);

	FTimerHandle GameStartTimer;
	Owner->GetWorldTimerManager().SetTimer(GameStartTimer, this, 
	&UROSImagePublisher::EnqueueImageTask, Period, true, Delay);
}

// Called when game ends or actor deleted
void UROSImagePublisher::EndPlay(const EEndPlayReason::Type Reason)
{

    Super::EndPlay(Reason);

    //FPlatformProcess()

    Handler->Disconnect();
    
}

// Called every frame
void UROSImagePublisher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    // UE_LOG(LogTemp, Warning, TEXT("Inside Component Tick for Image Publisher"));
    while (!PendingTasksROS.IsEmpty())
	{
		FGTCaptureTask Task;
		PendingTasksROS.Peek(Task);
		uint64 CurrentFrame = GFrameCounter;

		int32 SkipFrame = 1;
		if (!(CurrentFrame > Task.CurrentFrame + SkipFrame)) // TODO: This is not an elegant solution, fix it later.
		{ // Wait for the rendering thread to catch up game thread.
            UE_LOG(LogTemp, Warning, TEXT("Skipping a frame in Image Publisher tick component"));
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
<<<<<<< HEAD
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

            // Send to ROS asynchronously!
=======
            // TODO: ASYNC
            //SendToROS();

            // Serialise 
            TArray<uint8> ImgData = GTCapturer->CaptureNpyUint8(TEXT("lit"), channels);
		    UE_LOG(LogTemp, Warning, TEXT("captured!"));
       
            // TODO check that this timing is right - if it is actually captured a lot later, and the time stamp is from now, then it might not be correct
            auto Header = std_msgs::Header(++Count, FROSTime(), TEXT("0"));
            
            // Instantiate a copy of the actual task, and queue the task for execution with StartBackgroundTask()
>>>>>>> bc6ee48153eb6bf8ecedc6f3be7d7b8e786a38ea
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

void UROSImagePublisher::EnqueueImageTask()
{
    GTCapturer->SetWorldLocation(Owner->GetActorLocation()+FVector(0,0,50));
    // check(CaptureComponents.Num() != 0);
	USceneCaptureComponent2D* CaptureComponent = GTCapturer->GetCaptureComponent(Modes[0]);
	if (CaptureComponent == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Null pointer for capture component in enqueue ROS Task"));// return nullptr;

	const FRotator PawnViewRotation = CastedPawn->GetActorRotation();
	if (!PawnViewRotation.Equals(CaptureComponent->GetComponentRotation()))
	{
		CaptureComponent->SetWorldRotation(PawnViewRotation);
	}
    FString InFilename = TEXT("test_async.png");
	FAsyncRecord* AsyncRecord = FAsyncRecord::Create();
	FGTCaptureTask GTCaptureTask = FGTCaptureTask(Modes[0], InFilename, GFrameCounter, AsyncRecord);
	PendingTasksROS.Enqueue(GTCaptureTask);
}