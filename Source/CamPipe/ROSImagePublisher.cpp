// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSImagePublisher.h"
#include "sensor_msgs/CompressedImage.h"
#include "TimerManager.h"
#include "ROSLoggerSimState.h"
#include "GTCaptureComponent.h"
#include "Archive.h"
#include "FileHelper.h"

//~~~ Image Wrapper ~~~
#include "ImageUtils.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Engine/TextureRenderTarget2D.h"
//~~~ Image Wrapper ~~~


// Sets default values for this component's properties
UROSImagePublisher::UROSImagePublisher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Set rostopic name which publish strings
    Topic = TEXT("SomeImage");
    Type = TEXT("sensor_msgs/CompressedImage");

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

	FTimerHandle GameStartTimer;
	Owner->GetWorldTimerManager().SetTimer(GameStartTimer, this, 
	&UROSImagePublisher::SendToROS, 1.0f, true, 5.0f);
	
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
    Handler->Process();
    UE_LOG(LogTemp, Warning, TEXT("tick"));

}

void UROSImagePublisher::SendToROS()
{
    //FAsyncRecord* CheckAsyncRecord = GTCapturer->Capture(Modes[0], TEXT("test.png"));

    APawn* CastedPawn = Cast<APawn>(Owner);

    TArray<FString> Modes;
    Modes.Add(TEXT("lit"));
    GTCapturer = UGTCaptureComponent::Create(CastedPawn, Modes);

    // TO capture data 
    //TArray<uint8> ImgData = GTCapturer->CapturePng(Modes[0]);
    //TArray<FColor> ImgData = GTCapturer->CapturePng(Modes[0]);
    //TArray<uint8> ImgData = GTCapturer->CaptureNpyUint8(Modes[0], (int32)3);
    
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

    /* //////////////////////////////////
    //ros stuff

    uint32 height = 480;
    uint32 width = 640;
    uint32 step = 640*3;
    FString format = TEXT("png");


    TSharedPtr<sensor_msgs::CompressedImage> ImageFromUCV =
           MakeShareable(new sensor_msgs::CompressedImage());
    ImageFromUCV->SetHeader(std_msgs::Header(++Count, FROSTime(), TEXT("0")));
    ImageFromUCV->SetFormat(format);
    ImageFromUCV->SetData(Img);

    // if(!ImageFromUCV.IsValid())
    // {
    //    UE_LOG(LogTemp, Warning, TEXT("ImageFromUCV is null"));
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("ImageFromUCV alloc!"));
    // }

    Handler->PublishMsg(Topic, ImageFromUCV);

    //UE_LOG(LogTemp, Warning, TEXT("ImageFromUCV = %s"), *ImageFromUCV->ToString());
    */

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


