// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROSBridgeHandler.h"
#include "CamPublisher.generated.h"

UCLASS()
class CAMPIPE_API ACamPublisher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACamPublisher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type Reason);

    // Add a smart pointer to ROSBridgeHandler
    TSharedPtr<FROSBridgeHandler> Handler;

    // Add a ROSBridgePublisher smart pointer
    TSharedPtr<FROSBridgePublisher> Publisher;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    FString IPAddress;

    UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    uint32 Port;

    UPROPERTY(EditAnywhere, Category = "ROS Publisher")
    FString Topic;

	
};
