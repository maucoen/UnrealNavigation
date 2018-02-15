// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSImagePublisher.h"
#include "sensor_msgs/CompressedImage.h"
#include "TimerManager.h"
#include "ROSLoggerSimState.h"
#include "GTCaptureComponent.h"


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

    APawn* CastedPawn = Cast<APawn>(Owner);

    TArray<FString> Modes;
    Modes.Add(TEXT("lit"));

    //UE_LOG(LogTemp, Warning, TEXT("about to create gtcapture"));
    UGTCaptureComponent* GTCapturer = UGTCaptureComponent::Create(CastedPawn, Modes);

    // TO capture data 
    TArray<uint8> ImgData = GTCapturer->CapturePng(Modes[0]);
    //TArray<uint8> ImgData = GTCapturer->CaptureNpyUint8(Modes[0], (int32)3);
    
    // UE_LOG(LogTemp, Warning, TEXT("about to print npy")); 

    //     for (int32 b = 0; b < 200; b++)
    //  {
    //      UE_LOG(LogTemp, Warning, TEXT("%d"), ImgData[b]); 
    //  }
    // ImgData.RemoveAtSwap(0,80,true);

    // UE_LOG(LogTemp, Warning, TEXT("about to print removed"));

    //        for (int32 b = 0; b < 200; b++)
    //  {
    //      UE_LOG(LogTemp, Warning,  TEXT("%d"), ImgData[b]); 
    //  }

    uint32 height = 480;
    uint32 width = 640;
    uint32 step = 640*3;
    FString format = TEXT("png");


    TSharedPtr<sensor_msgs::CompressedImage> ImageFromUCV =
           MakeShareable(new sensor_msgs::CompressedImage());
    ImageFromUCV->SetHeader(std_msgs::Header(++Count, FROSTime(), TEXT("0")));
    ImageFromUCV->SetFormat(format);
    ImageFromUCV->SetData(ImgData);

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


}


