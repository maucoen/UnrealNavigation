// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ROSBridgeHandler.h"
#include "sensor_msgs/CompressedImage.h"
#include "sensor_msgs/Image.h"
#include "GTCaptureComponent.h"
#include "AsyncWork.h"
#include "ROSImagePublisher.generated.h"


// UENUM(BlueprintType)		//"BlueprintType" is essential to include
// enum class EImageTypeEnum : uint8
// {
//         RGBD 	UMETA(DisplayName="RGBD"),
//         MONO 	UMETA(DisplayName="Monocular"),
// 		STEREO	UMETA(DisplayName="Stereo")
// };

UENUM(BlueprintType)
namespace EImagingType
{
	enum Type 
	{	
		MONO	UMETA(DisplayName = "Monocular"),
		RGBD	UMETA(DisplayName = "RGBD"),
		STEREO 	UMETA(DisplayName = "Stereo"),
	};
}

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALNAVIGATION_API UROSImagePublisher : public UActorComponent
{
	GENERATED_BODY()

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Enum)
	// EImageTypeEnum Imaging;



public:	
	// Sets default values for this component's properties
	UROSImagePublisher();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type Reason);

	void EnqueueImageTask();
		
	//UGTCaptureComponent* GTCapturer;

	TArray<UGTCaptureComponent*> GTCapturers;

	struct FTimerHandle GameStartTimer;

	class std_msgs::Header ROSHeader;
	APawn* CastedPawn;
	TQueue<FGTCaptureTask, EQueueMode::Spsc> PendingTasksROS;
	//TQueue<FVector, EQueueMode::Spsc> PendingTasks;

	uint32 channels = 3;
	uint32 Count = 0;
	TArray<FString> Modes;
	TArray<FString> Topics;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
	TEnumAsByte<EImagingType::Type > ImagingType;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    AActor* Owner;

	// Add a smart pointer to ROSBridgeHandler
    TSharedPtr<FROSBridgeHandler> Handler;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    FString IPAddress = TEXT("127.0.1.1");

    UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    uint32 Port = 9090;

	// UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    // FString Topic = TEXT("/camera/image_raw");

    FString Type = TEXT("sensor_msgs/Image"); 

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    float Delay = 2.0f;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    float Frequency = 1.0f;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    uint32 MaxImages = 50;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
	bool bIsCompressed = false;

};

// This is our async task
class FSendToROS : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FSendToROS>;
 
public:
	FSendToROS(
		TSharedPtr<FROSBridgeHandler> InHandler,
		TArray<uint8> &InImgData,
		std_msgs::Header &InHeader,
		FString InTopic,
		bool InbIsCompressed) 
		:
		Handler(InHandler),
		ImgData(InImgData),
		Header(InHeader),
		Topic(InTopic),
		bIsCompressed(InbIsCompressed)
	{}

protected:
	TSharedPtr<FROSBridgeHandler> Handler;
	TArray<uint8> ImgData;
	std_msgs::Header Header;
	FString Topic;
	bool bIsCompressed;
	
	// HARD Settings, check unrealcv.ini before starting up
	uint32 height = 400;
    uint32 width = 400;
    uint32 step = width*3;
    FString encoding = TEXT("rgb8");
    uint8 isbigendian = 0;
	FString format = TEXT("png");

	void DoWork() 
	{
		if (bIsCompressed)
		{
			TSharedPtr<sensor_msgs::CompressedImage> CompressedData =
            MakeShareable(new sensor_msgs::CompressedImage(
                Header,
                format,
                ImgData
            ));			
			if (Handler.IsValid()) Handler->PublishMsg(Topic, CompressedData);
		}
		else
		{
			TSharedPtr<sensor_msgs::Image> ImageData =
            MakeShareable(new sensor_msgs::Image(
                Header,
                height,
                width,
                encoding,
                isbigendian,
                step,
                ImgData
            ));
			if (Handler.IsValid()) Handler->PublishMsg(Topic, ImageData);
		}
	}
 
	// This next section of code needs to be here
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FSendToROS, STATGROUP_ThreadPoolAsyncTasks);
	}
};

// // timer with inputs
// // CPP FILE
// FTimerDelegate TimerDel;
// FTimerHandle TimerHandle;
// // Params to pass into function once it ticks
// int32 MyInt = 10;
// float MyFloat = 20.f;
// //Binding the function with specific variables
// TimerDel.BindUFunction(this, FName("MyUsefulFunction"), MyInt, MyFloat);
// //Calling MyUsefulFunction after 5 seconds without looping
// GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 5.f, false);
// // HEADER FILE
// UFUNCTION()
// void MyUsefulFunction(int32 x, float y);