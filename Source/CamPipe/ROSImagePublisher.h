// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "ROSBridgeHandler.h"
#include "UnrealNetwork.h"
#include "GTCaptureComponent.h"
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

	void EnqueueROSTask();

	void SendToROS(UTextureRenderTarget2D* RenderTarget);

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
    FString IPAddress;

    UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    uint32 Port;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    FString Topic;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    FString Type;

	class UGTCaptureComponent* GTCapturer;

	TArray<uint8> SceneCapture(USceneCaptureComponent2D* This);

private:

	APawn* CastedPawn;

	TQueue<FGTCaptureTask, EQueueMode::Spsc> PendingTasksROS;
	// TMap<FString, USceneCaptureComponent2D*> CaptureComponents;
};
