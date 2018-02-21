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
            Topics.Add(TEXT("/camera/image_raw"));
            GTCapturers.Add(UGTCaptureComponent::Create(CastedPawn, Modes));

        for (FString Topic : Topics)
            {
                Handler->AddPublisher(
		        MakeShareable<FROSBridgePublisher>(
                    new FROSBridgePublisher(Topic, Type)));
            }
            break;
        }

        case EImagingType::RGBD:
        {
            Modes.Add(TEXT("lit"));
            Modes.Add(TEXT("vis_depth")); 
            GTCapturers.Add(UGTCaptureComponent::Create(CastedPawn, Modes));
            
            Topics.Add(TEXT("/camera/image_raw"));
            Topics.Add(TEXT("/camera/depth_registered/image_raw"));

            for (FString Topic : Topics)
            {
                Handler->AddPublisher(
		        MakeShareable<FROSBridgePublisher>(
                    new FROSBridgePublisher(Topic, Type)));
            }
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

            for (FString Topic : Topics)
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

        FVector eye = FVector(0,50,00);
 
        for (int i=0; i < Modes.Num(); i++)
        {

            GTCapturers[i]->SetWorldLocation(Owner->GetActorLocation());
            GTCapturers[i]->AddRelativeLocation(FVector(0,0,100));
            if (i>0) //&& (Modes[i] == TEXT("lit"))) //stereo eye
            {
                GTCapturers[i]->AddRelativeLocation(eye);
            }
            
		    USceneCaptureComponent2D* CaptureComponent = GTCapturers[i]->GetCaptureComponent(Modes[i]);
		            
            // check(CaptureComponents.Num() != 0);
            // USceneCaptureComponent2D* CaptureComponent = GTCapturer->GetCaptureComponent(Mode);
	            if (CaptureComponent == nullptr)
                {
                    UE_LOG(LogTemp, Warning, TEXT("NULL Capture! No enqueue")); 
                    return;
                }
                const FRotator PawnViewRotation = CastedPawn->GetActorRotation();
	            if (!PawnViewRotation.Equals(CaptureComponent->GetComponentRotation()))
	            {
		            CaptureComponent->SetWorldRotation(PawnViewRotation+FRotator(0,20,0));
	            }
            

            if (CaptureComponent == nullptr)
		    {
			    UE_LOG(LogTemp, Warning, TEXT("Unrecognized capture mode %s"), *Modes[i]);
		    }
		    else
		    {
                
                // Capture Image; 
                TArray<uint8> ImgData;
                if (bIsCompressed)
                {
                    ImgData = GTCapturers[i]->CapturePng(Modes[i]);
                }
                else 
                {
		            ImgData = GTCapturers[i]->CaptureNpyUint8(Modes[i], channels);
                }
                ROSHeader.SetSeq(++Count);
		        ROSHeader.SetStamp(FROSTime());


                FString Filename = FString::FromInt(Count) + Modes[i]+ FString::FromInt(i)+ TEXT(".png");
                
                GTCapturers[i]->SavePng(GTCapturers[i]->GetCaptureComponent(Modes[i])->TextureTarget,Filename);
            
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
		Task.AsyncRecord->bIsCompleted = true;
    }
    if(Handler.IsValid()) Handler->Process();
}

void UROSImagePublisher::EnqueueImageTask()
{

        // Setup Publisher to publish the correct types
    switch(ImagingType)
    {
        case EImagingType::MONO:
        {
            GTCapturers[0]->SetWorldLocation(Owner->GetActorLocation()+FVector(0,0,150));
            // check(CaptureComponents.Num() != 0);

            for (FString Mode : Modes)
            {
                USceneCaptureComponent2D* CaptureComponent = GTCapturers[0]->GetCaptureComponent(Mode);
	            if (CaptureComponent == nullptr)
                {
                    UE_LOG(LogTemp, Warning, TEXT("NULL Capture! No enqueue")); 
                    return;
                }
                const FRotator PawnViewRotation = CastedPawn->GetActorRotation();
	            if (!PawnViewRotation.Equals(CaptureComponent->GetComponentRotation()))
	            {
		            CaptureComponent->SetWorldRotation(PawnViewRotation+FRotator(0,10,0));
	            }
            }
	        
            FString InFilename = FString::FromInt(Count) + TEXT("mono.png");
	        FAsyncRecord* AsyncRecord = FAsyncRecord::Create();
	        FGTCaptureTask GTCaptureTask = FGTCaptureTask(Modes[0], InFilename, GFrameCounter, AsyncRecord);
	        PendingTasksROS.Enqueue(GTCaptureTask);
            break;
        }

        case EImagingType::RGBD:
        {

	        
            FString InFilename = FString::FromInt(Count) + TEXT("mono.png");
	        FAsyncRecord* AsyncRecord = FAsyncRecord::Create();
	        FGTCaptureTask GTCaptureTask = FGTCaptureTask(Modes[0], InFilename, GFrameCounter, AsyncRecord);
	        PendingTasksROS.Enqueue(GTCaptureTask);
            break;
        }

        case EImagingType::STEREO:
        {
            
  
	        
            FString InFilename = FString::FromInt(Count) + TEXT("mono.png");
	        FAsyncRecord* AsyncRecord = FAsyncRecord::Create();
	        FGTCaptureTask GTCaptureTask = FGTCaptureTask(Modes[0], InFilename, GFrameCounter, AsyncRecord);
	        PendingTasksROS.Enqueue(GTCaptureTask);
            break;
        }
    }
}

          // //FVector eye = FVector(0,0,120);
            // for (FString Mode : Modes)
            // {
                
            //     //GTCapturer[i]->SetWorldLocation(Owner->GetActorLocation());
            //     //GTCapturers[i]->AddLocalOffset(eye);
            //     USceneCaptureComponent2D* CaptureComponent = GTCapturer->GetCaptureComponent(Mode);
	        //     if (CaptureComponent == nullptr)
            //     {
            //         UE_LOG(LogTemp, Warning, TEXT("NULL Capture! No enqueue")); 
            //         return;
            //     }
            //     const FRotator PawnViewRotation = CastedPawn->GetActorRotation();
	        //     if (!PawnViewRotation.Equals(CaptureComponent->GetComponentRotation()))
	        //     {
		    //         CaptureComponent->SetWorldRotation(PawnViewRotation+FRotator(0,10,0));
	        //     }
            //     /eye+=FVector(0,10,0); //offset the next capturer by 10cm to the right
            // }