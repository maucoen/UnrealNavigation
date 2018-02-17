// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "ROSBridgeHandler.h"
#include "sensor_msgs/CompressedImage.h"
#include "sensor_msgs/Image.h"
#include "UnrealNetwork.h"
#include "GTCaptureComponent.h"
#include "AsyncWork.h"
#include "ROSImagePublisher.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMPIPE_API UROSImagePublisher : public USceneCaptureComponent2D
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UROSImagePublisher();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type Reason);

	void EnqueueImageTask();

	void SendToROS();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

 	// Add a smart pointer to ROSBridgeHandler

    UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    AActor* Owner;

	uint32 Count;

	// Add a smart pointer to ROSBridgeHandler
    TSharedPtr<FROSBridgeHandler> Handler;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    FString IPAddress = TEXT("127.0.1.1");

    UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    uint32 Port = 9090;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    FString Topic = TEXT("SomeImage");

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    FString Type = TEXT("sensor_msgs/Image"); 

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    float Delay = 2.0f;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    float Period = 0.5f;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
	int32 SendCompressed = 0;

	UGTCaptureComponent* GTCapturer;

	//TArray<uint8> SceneCapture(USceneCaptureComponent2D* This);

private:

	APawn* CastedPawn;

	TQueue<FGTCaptureTask, EQueueMode::Spsc> PendingTasksROS;
	// TMap<FString, USceneCaptureComponent2D*> CaptureComponents;

	// ROS Image based on GTCapturer settings
	// HARD Settings, don't change
	uint32 height = 480;
    uint32 width = 640;
    uint32 step = 640*3;
    FString encoding = TEXT("rgb8");//TEXT("bgr8"); //bgra8
    uint8 isbigendian = 0;
    FString format = TEXT("png");
	uint32 channels = 3;


};

// This is our async task
class FSendToROS : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FSendToROS>;
	//friend class sensor_msgs::Image
	friend class FROSBridgeHandler;
	friend class UGTCaptureComponent;
 
public:
	FSendToROS(
		TSharedPtr<FROSBridgeHandler> InHandler,
		TArray<uint8> &InImgData,
		std_msgs::Header InHeader,
		FString InTopic) 
		:
		Handler(InHandler),
		ImgData(InImgData),
		Header(InHeader),
		Topic(InTopic)
	{
		UE_LOG(LogTemp, Warning, TEXT("FSendToROS initializer worked")); 
	}
 
protected:
	TSharedPtr<FROSBridgeHandler> Handler;
	TArray<uint8> ImgData;
	std_msgs::Header Header;
	FString Topic;

	uint32 height = 480;
    uint32 width = 640;
    uint32 step = 640*3;
    FString encoding = TEXT("rgb8");
    uint8 isbigendian = 0;
	uint32 channels = 3;
 
	void DoWork() 
	{
		UE_LOG(LogTemp, Warning, TEXT("FSendToROS about to capture"));
		 //Construct with set values
        TSharedPtr<sensor_msgs::Image> ImageFromUCV =
            MakeShareable(new sensor_msgs::Image(
                Header,
                height,
                width,
                encoding,
                isbigendian,
                step,
                ImgData
            ));

		UE_LOG(LogTemp, Warning, TEXT("made sensor Image!"));
        
		//this is the slow guy

		if (Handler.IsValid()) Handler->PublishMsg(Topic, ImageFromUCV);
	}
 
	// This next section of code needs to be here.  Not important as to why.
 
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FSendToROS, STATGROUP_ThreadPoolAsyncTasks);
	}
};
