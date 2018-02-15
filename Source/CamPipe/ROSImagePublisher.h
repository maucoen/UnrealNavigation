// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ROSBridgeHandler.h"
#include "UnrealNetwork.h"
#include "ROSImagePublisher.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMPIPE_API UROSImagePublisher : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UROSImagePublisher();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type Reason);

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
    FString IPAddress;

    UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    uint32 Port;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    FString Topic;

	UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    FString Type;

};
