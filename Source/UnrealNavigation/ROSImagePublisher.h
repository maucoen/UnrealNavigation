// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "ROSBridgeHandler.h"
#include "sensor_msgs/CompressedImage.h"
#include "sensor_msgs/Image.h"
#include "px4_msgs/PolyTraj.h"

#include "GTCaptureComponent.h"
#include "AsyncWork.h"
#include "ROSImagePublisher.generated.h"


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
class UNREALNAVIGATION_API AROSImagePublisher : public ACameraActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AROSImagePublisher(const FObjectInitializer& ObjectInitializer);

	void CreateSplineMesh();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void SetupImager();
	virtual void EndPlay(const EEndPlayReason::Type Reason);

	void EnqueueImageTask();

	void ToggleImaging();
	bool bIsImaging = false;

	void ToggleNavigation();
	bool bIsNavigating = false;
	float StartTime = 0.0f;
	float ElapsedTime = 0.0f;
	
	void PublishGoal();
	

	TArray<UGTCaptureComponent*> GTCapturers;
	struct FTimerHandle PublishTimer;
	struct FTimerHandle TrajTimer;

	class std_msgs::Header ROSHeader;
	
	//TQueue<FGTCaptureTask, EQueueMode::Spsc> PendingTasksROS;
	TQueue<uint64, EQueueMode::Spsc> LastFrame;

	uint32 channels = 3;
	uint32 Count = 0;
	TArray<FString> Modes;
	TArray<FString> Topics;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
	TEnumAsByte<EImagingType::Type > ImagingType;

	FTransform GoToState;
	FTransform StartingBodyState;

public:	

	void SetNewState(FTransform InState)
	{
		GoToState = InState;
	}
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
	AActor* CastedPawny;

	// Add a smart pointer to ROSBridgeHandler
    TSharedPtr<FROSBridgeHandler> Handler;
	TSharedPtr<class FPolyTrajSubscriber> PolyTrajSubscriber;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    FString IPAddress = TEXT("127.0.1.1");

    UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    uint32 Port = 9090;

    FString Type = TEXT("sensor_msgs/Image"); 

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    float Delay = 2.0f;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    float Frequency = 1.0f;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    FVector StereoBaselineCm = {0,500,0};

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
	bool bSaveToDisk = false;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
	bool bIsCompressed = false;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
	bool bCometGazingMode = false;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
	class AStaticMeshActor* Comet;

	UPROPERTY(EditAnywhere, Category = Mesh)
    class USplineComponent* Spline;
	
	UPROPERTY()
	TArray<class USplineMeshComponent*> SplineMesh;

	UPROPERTY(EditAnywhere, Category = Mesh)
	class UStaticMesh* StatMesh;

	UPROPERTY(EditAnywhere, Category = Goal)
	class APawn* GoalPawn;

	

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
	
	// HARD Settings, check unrealcv.ini,(UnrealEngine/Engine/Binaries/Linux/unrealcv.ini) orbslam yamls before starting up
	uint32 height = 480;
    uint32 width = 640;
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
			if (Handler.IsValid())
			{
				Handler->PublishMsg(Topic, CompressedData);
			} 		
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
			if (Handler.IsValid())
			{
				Handler->PublishMsg(Topic, ImageData);
				//UE_LOG(LogTemp, Warning, TEXT("Handler published"));
			} 
		}
	}
 
	// Stats for profiling the thread
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