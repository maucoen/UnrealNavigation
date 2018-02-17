// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSImagePublisher.h"
#include "sensor_msgs/CompressedImage.h"
#include "sensor_msgs/Image.h"
#include "TimerManager.h"
#include "ROSLoggerSimState.h"
#include "GTCaptureComponent.h"
#include "Archive.h"
#include "FileHelper.h"

#include "CaptureManager.h"

//~~~ Image Wrapper ~~~
#include "ImageUtils.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Engine/TextureRenderTarget2D.h"
//~~~ Image Wrapper ~~~

// DECLARE_CYCLE_STAT(TEXT("EnqueueROSTask"), STAT_EnqueueROSTask, STATGROUP_UnrealCV);

// Sets default values for this component's properties
UROSImagePublisher::UROSImagePublisher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set rostopic name which publish strings
    Topic = TEXT("SomeImage");
    // Type = TEXT("sensor_msgs/CompressedImage");
    Type = TEXT("sensor_msgs/Image"); 

	Owner = GetOwner();

    	// Set websocket server address to the ros IP address
    IPAddress = TEXT("127.0.1.1");
    // Set Port to 9090
    Port = 9090;

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
	GTCapturer = UGTCaptureComponent::Create(CastedPawn, Modes);
	// this->CaptureComponents.Add(Capturer);

    // PrimaryComponentTick.bCanEverTick = true;

	FTimerHandle GameStartTimer;
	Owner->GetWorldTimerManager().SetTimer(GameStartTimer, this, 
	&UROSImagePublisher::EnqueueROSTask, 5.0f, true, 5.0f);
	
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
			
			//UE_LOG(LogUnrealCV, Warning, TEXT("about to save png"));
			//ImgAData.Empty();
			// GTCapturer->SavePng(CaptureComponent->TextureTarget, Task.Filename);

            SendToROS(CaptureComponent->TextureTarget);
				
		}
		Task.AsyncRecord->bIsCompleted = true;
    }

    
    if(Handler.IsValid()) Handler->Process();
    // UE_LOG(LogTemp, Warning, TEXT("tick"));

}

void UROSImagePublisher::EnqueueROSTask()
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

    // return AsyncRecord;
}

void UROSImagePublisher::SendToROS(UTextureRenderTarget2D* RenderTarget)
{
    int32 compressedFlag = 0;

    if (compressedFlag == 1)
    {
        TArray<uint8> ImgData = GTCapturer->ExportPngCompressed(RenderTarget);

        UE_LOG(LogTemp, Warning, TEXT("size of ImgData: %d"), ImgData.Num());
    
        FString format = TEXT("png");
        
        TSharedPtr<sensor_msgs::CompressedImage> ImageFromUCV =
           MakeShareable(new sensor_msgs::CompressedImage());
        ImageFromUCV->SetHeader(std_msgs::Header(++Count, FROSTime(), TEXT("0")));
        ImageFromUCV->SetFormat(format);
        ImageFromUCV->SetData(ImgData);


        Handler->PublishMsg(Topic, ImageFromUCV);
    }
    else
    {
        // Get raw data
        TArray<FColor> ImgDataFColor = GTCapturer->ExportPng(RenderTarget);
        // Serialise 
        uint32 channel = 3;
        TArray<uint8> ImgData = GTCapturer->CaptureNpyUint8(TEXT("lit"), channel);

        UE_LOG(LogTemp, Warning, TEXT("size of ImgData: %d"), ImgData.Num());

        uint32 height = 480;
        uint32 width = 640;
        uint32 step = 640*3;
        FString encoding = TEXT("rgb8");//TEXT("bgr8"); //bgra8
        uint8 isbigendian = 0;
        FString format = TEXT("png");

        TSharedPtr<sensor_msgs::Image> ImageFromUCV =
            MakeShareable(new sensor_msgs::Image());
        ImageFromUCV->SetHeader(std_msgs::Header(++Count, FROSTime(), TEXT("0")));
        ImageFromUCV->SetHeight(height);
        ImageFromUCV->SetWidth(width);
        ImageFromUCV->SetEncoding(encoding);
        ImageFromUCV->SetIsBigEndian(isbigendian);
        ImageFromUCV->SetStep(step);
        ImageFromUCV->SetData(ImgData);

        Handler->PublishMsg(Topic, ImageFromUCV);
    }


    
    // OLD
    
    // for (int32 b = 1; b < ImgData.Num(); b=b+50005)
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("ImgData %d"), ImgData[b]); 
    //     // UE_LOG(LogTemp, Warning, TEXT("ImgData %d"), GTCapturer->ImgAData[b]);
    // }
    
    // SCOPE_CYCLE_COUNTER(STAT_EnququeROSTask);
    
    //FAsyncRecord* CheckAsyncRecord = GTCapturer->Capture(Modes[0], TEXT("test.png"));

    // APawn* CastedPawn = Cast<APawn>(Owner);

    // TArray<FString> Modes;
    // Modes.Add(TEXT("lit"));

    //FCaptureManager::Get().AttachGTCaptureComponentToCamera(CastedPawn);

    // UGTCaptureComponent* GTCapturer = UGTCaptureComponent::Create(CastedPawn, Modes);

    // int32 CameraId = FCString::Atoi(TEXT("0"));
    // UGTCaptureComponent* GTCapturer = FCaptureManager::Get().GetCamera(CameraId);
    // if (GTCapturer == nullptr)
	// {
	// 	UE_LOG(LogTemp,Warning,TEXT("Invalid camera id %d"), CameraId);
	// }

    // GTCapturer->Capture(Modes[0], TEXT("test_002.png"));

    // TO capture data 
    // TArray<uint8> ImgData = GTCapturer->CapturePng(Modes[0]);
    //TArray<FColor> ImgData = GTCapturer->CapturePng(Modes[0]);
    // TArray<uint8> ImgData = GTCapturer->CaptureNpyUint8(Modes[0], (int32)4);

    // TArray<uint8> ImgData = GTCapturer->ExportPng(Modes[0]);
    
    //GTCapturer->Capture(Modes[0], TEXT("test.png"));

    
    



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


    /*//////////////////////////////////////
    //direct serilization (in built)
    
    FBufferArchive ImgBinary;
    //ImgData.BulkSerialize(ImgBinary);
    
    //ImgBinary.PopDebugDataString();
    
    //ImgBinary.PopEditorOnlyProperty();
    
    //ImgBinary << ImgData;

    //UE_LOG(LogTemp, Warning, TEXT("ImgBin %d"), ImgBinary.Num());  
    */


    /* ///////////////////////////////////////
    //manual saving

    FString path = TEXT("/home/mau/EPIC/Projects/CamPipe/")+(FString::FromInt(Count)) + TEXT("te.png");

    UE_LOG(LogTemp, Warning, TEXT("path %s"), *path);
    
    
    bool suc = FFileHelper::SaveArrayToFile(Img, *path);

    if (!suc)    UE_LOG(LogTemp, Warning, TEXT("not saved"));
    */

     //////////////////////////////////
    //ros stuff






    // if(!ImageFromUCV.IsValid())
    // {
    //    UE_LOG(LogTemp, Warning, TEXT("ImageFromUCV is null"));
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("ImageFromUCV alloc!"));
    // }


    //UE_LOG(LogTemp, Warning, TEXT("ImageFromUCV = %s"), *ImageFromUCV->ToString());
    

}

//Made my own scene capturer to see if this works
TArray<uint8> UROSImagePublisher::SceneCapture(USceneCaptureComponent2D* Target) //, const FString ImagePath, const FLinearColor ClearColour)
{
    if (this == nullptr) 
    {
        UE_LOG(LogTemp, Warning, TEXT("tar is null"));
     	return TArray<uint8>();
    }
    this->TextureTarget = NewObject<UTextureRenderTarget2D>();
    this->TextureTarget->InitAutoFormat(640, 480);
	this->FOVAngle = 100;

    this->CaptureScene();
    //this->TextureTarget->UpdateResourceImmediate();
	if (this->TextureTarget == nullptr)
	{
        UE_LOG(LogTemp, Warning, TEXT("textar is null"));
     	return TArray<uint8>();
	}
	
	FRenderTarget* RenderTarget = this->TextureTarget->GameThread_GetRenderTargetResource();
	if (RenderTarget == nullptr)
	{
        UE_LOG(LogTemp, Warning, TEXT("rendertar is null"));
     	return TArray<uint8>();
	}

	TArray<FColor> RawPixels;
    RenderTarget->ReadPixels(RawPixels);

    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG); 

	const int32 Width = Target->TextureTarget->SizeX;
	const int32 Height = Target->TextureTarget->SizeY;
	
	if (ImageWrapper.IsValid() && ImageWrapper->SetRaw(&RawPixels[0], RawPixels.Num() * sizeof(FColor), Width, Height, ERGBFormat::BGRA, 8))
	{
		return ImageWrapper->GetCompressed();
	}
    else return TArray<uint8>();
}


