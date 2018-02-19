// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSImagePublisher.h"
#include "TimerManager.h"
//#include "ROSLoggerSimState.h"
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

    if (Count == StopAt)
    {
        GetWorld()->GetTimerManager().ClearTimer(GameStartTimer);
        UE_LOG(LogTemp, Warning, TEXT("Clearing publishing"));
        PendingTasksROS.Empty();
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

void UROSImagePublisher::EnqueueImageTask()
{
    GTCapturer->SetWorldLocation(Owner->GetActorLocation()+FVector(0,0,150));
    // check(CaptureComponents.Num() != 0);
	USceneCaptureComponent2D* CaptureComponent = GTCapturer->GetCaptureComponent(Modes[0]);
	if (CaptureComponent == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Null pointer for capture component in enqueue ROS Task"));// return nullptr;

	const FRotator PawnViewRotation = CastedPawn->GetActorRotation();
	if (!PawnViewRotation.Equals(CaptureComponent->GetComponentRotation()))
	{
		CaptureComponent->SetWorldRotation(PawnViewRotation);
	}
    FString InFilename = FString::FromInt(Count) + TEXT("test_async.png");
	FAsyncRecord* AsyncRecord = FAsyncRecord::Create();
	FGTCaptureTask GTCaptureTask = FGTCaptureTask(Modes[0], InFilename, GFrameCounter, AsyncRecord);
	PendingTasksROS.Enqueue(GTCaptureTask);
}