// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSImagePublisher.h"

#include "TimerManager.h"
#include "ROSLoggerSimState.h"
#include "CaptureManager.h"


// DECLARE_CYCLE_STAT(TEXT("EnqueueROSTask"), STAT_EnqueueROSTask, STATGROUP_UnrealCV);

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
    
    auto Root = Owner->GetRootComponent();
    UE_LOG(LogTemp, Warning, TEXT("root worked"));
    this->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
    Count = 1;

    // Set websocket server address to default
    Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(IPAddress, Port));

         // **** Create publishers here ****
	Handler->AddPublisher(
		MakeShareable<FROSBridgePublisher>(
        new FROSBridgePublisher(Topic, Type)));

           	//Connect to ROSBridge Websocket server.
    Handler->Connect();

    // Initialised Capture Components list 
    CastedPawn = Cast<APawn>(Owner);

    TArray<FString> Modes;
    Modes.Add(TEXT("lit"));

    // this->CaptureComponents.Empty();
    // link capturer with pawn
	// this->CaptureComponents.Add(Capturer);

    GTCapturer = UGTCaptureComponent::Create(CastedPawn, Modes);
    // Set websocket server address to default
    //oldGTCapturer = MakeShareable(new UGTCaptureComponent);
    //oldGTCapturer->Create(CastedPawn, Modes);
    
    //GTCapturer = MakeShareable<UGTCaptureComponent>(GTCapturerOld);
	

	FTimerHandle GameStartTimer;
	Owner->GetWorldTimerManager().SetTimer(GameStartTimer, this, 
	&UROSImagePublisher::EnqueueImageTask, Period, true, Delay);
	
}

// Called when game ends or actor deleted
void UROSImagePublisher::EndPlay(const EEndPlayReason::Type Reason)
{
    Handler->Disconnect();
    Super::EndPlay(Reason);
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

        UE_LOG(LogTemp, Warning, TEXT("Got suitable frame, now to process. In tick component"));
        
        PendingTasksROS.Dequeue(Task);
		USceneCaptureComponent2D* CaptureComponent = GTCapturer->GetCaptureComponent(Task.Mode);
		if (CaptureComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Unrecognized capture mode, in UROSImagePublisher Tick Component %s"), *Task.Mode);
		}
		else
		{
            // TODO: ASYNC
            //SendToROS();

            // Serialise 
            TArray<uint8> ImgData = GTCapturer->CaptureNpyUint8(TEXT("lit"), channels);
		    UE_LOG(LogTemp, Warning, TEXT("captured!"));
       

            auto Header = std_msgs::Header(++Count, FROSTime(), TEXT("0"));
            
            // Instantiate a copy of the actual task, and queue the task for execution with StartBackgroundTask()
            (new FAutoDeleteAsyncTask<FSendToROS>(
                Handler, 
                ImgData,
                Header,
                Topic
            ))->StartBackgroundTask();
				
		}
		Task.AsyncRecord->bIsCompleted = true;
    }
    
    if(Handler.IsValid()) Handler->Process();

}

void UROSImagePublisher::EnqueueImageTask()
{
    UE_LOG(LogTemp, Warning, TEXT("Inside EnqueueROSTask"));
    FString Mode = TEXT("lit");
    GTCapturer->SetWorldLocation(Owner->GetActorLocation()+FVector(0,0,50));
    // check(CaptureComponents.Num() != 0);
	USceneCaptureComponent2D* CaptureComponent = GTCapturer->GetCaptureComponent(Mode);
	if (CaptureComponent == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Null pointer for capture component in enqueue ROS Task"));// return nullptr;

	const FRotator PawnViewRotation = CastedPawn->GetActorRotation();
	if (!PawnViewRotation.Equals(CaptureComponent->GetComponentRotation()))
	{
		CaptureComponent->SetWorldRotation(PawnViewRotation);
	}

    FString InFilename = TEXT("test_async.png");
	FAsyncRecord* AsyncRecord = FAsyncRecord::Create();
	FGTCaptureTask GTCaptureTask = FGTCaptureTask(Mode, InFilename, GFrameCounter, AsyncRecord);
	PendingTasksROS.Enqueue(GTCaptureTask);
}

// TODO: Arguments should be crucial for asynchronous operations
void UROSImagePublisher::SendToROS() 
{
    if (SendCompressed == 0)
    {
        // Serialise 
        TArray<uint8> ImgData = GTCapturer->CaptureNpyUint8(TEXT("lit"), channels);

        //Construct with set values
        TSharedPtr<sensor_msgs::Image> ImageFromUCV =
            MakeShareable(new sensor_msgs::Image(
                std_msgs::Header(++Count, FROSTime(), TEXT("0")),
                height,
                width,
                encoding,
                isbigendian,
                step,
                ImgData
            ));

        Handler->PublishMsg(Topic, ImageFromUCV);
        
    }
    else
    {
        // TArray<uint8> ImgData = GTCapturer->ExportPngCompressed(RenderTarget);
        // TSharedPtr<sensor_msgs::CompressedImage> ImageFromUCV =
        //    MakeShareable(new sensor_msgs::CompressedImage(
        //        std_msgs::Header(++Count, FROSTime(), TEXT("0")),
        //        format,
        //        ImgData
        //    ));

        // Handler->PublishMsg(Topic, ImageFromUCV);

        // ImageFromUCV->SetHeader(std_msgs::Header(++Count, FROSTime(), TEXT("0")));
        // ImageFromUCV->SetFormat(format);
        // ImageFromUCV->SetData(ImgData);
    }
  
    /* ///////////////////////////////////
    //manual scene capturer

    TArray<uint8> Img = SceneCapture(this);

    //UE_LOG(LogTemp, Warning, TEXT("about to check size"));
    if (Img.Num() > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("size of Img %d"), Img.Num());
        //for (int32 b = 1; b < Img.Num(); b=b+50045)
        //{
           //UE_LOG(LogTemp, Warning, TEXT("ImgBin %d"), Img[b]); 
           //UE_LOG(LogTemp, Warning, TEXT("ImgBin %d"), GTCapturer->ImgAData[b]);
        //}
    }
    */
}
// //Manual scene capturer
// TArray<uint8> UROSImagePublisher::SceneCapture(USceneCaptureComponent2D* Target) //, const FString ImagePath, const FLinearColor ClearColour)
// {
//     if (this == nullptr) 
//     {
//         UE_LOG(LogTemp, Warning, TEXT("tar is null"));
//      	return TArray<uint8>();
//     }
//     this->TextureTarget = NewObject<UTextureRenderTarget2D>();
//     this->TextureTarget->InitAutoFormat(640, 480);
// 	this->FOVAngle = 100;

//     this->CaptureScene();
//     //this->TextureTarget->UpdateResourceImmediate();
// 	if (this->TextureTarget == nullptr)
// 	{
//         UE_LOG(LogTemp, Warning, TEXT("textar is null"));
//      	return TArray<uint8>();
// 	}
	
// 	FRenderTarget* RenderTarget = this->TextureTarget->GameThread_GetRenderTargetResource();
// 	if (RenderTarget == nullptr)
// 	{
//         UE_LOG(LogTemp, Warning, TEXT("rendertar is null"));
//      	return TArray<uint8>();
// 	}

// 	TArray<FColor> RawPixels;
//     RenderTarget->ReadPixels(RawPixels);

//     IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
// 	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG); 

// 	const int32 Width = Target->TextureTarget->SizeX;
// 	const int32 Height = Target->TextureTarget->SizeY;
	
// 	if (ImageWrapper.IsValid() && ImageWrapper->SetRaw(&RawPixels[0], RawPixels.Num() * sizeof(FColor), Width, Height, ERGBFormat::BGRA, 8))
// 	{
// 		return ImageWrapper->GetCompressed();
// 	}
//     else return TArray<uint8>();
// }


