// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ROSBridgeHandler.h"
#include "ROSBridgeSubscriber.h"
#include "geometry_msgs/Twist.h"
#include "WheeledVehicle.h"
#include "ROSControllerSubscriberCallback.h"
#include "Components/ActorComponent.h"
#include "ROSVehicleController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAMPIPE_API UROSVehicleController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UROSVehicleController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type Reason);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Add a smart pointer to ROSBridgeHandler
    TSharedPtr<FROSBridgeHandler> Handler;

	UPROPERTY(EditAnywhere, Category = "ROS Subscriber")
    FString IPAddress = TEXT("127.0.1.1");

    UPROPERTY(EditAnywhere, Category = "ROS Subscriber")
    uint32 Port = 9090;

 	// Add a smart pointer to ROSBridgeHandler
    UPROPERTY(EditAnywhere, Category = "ROS Subscriber")
    FString Topic = TEXT("cmd_vel");

	UPROPERTY(EditAnywhere, Category = "ROS Subscriber")
    FString Type = TEXT("geometry_msgs/Twist");

    UPROPERTY(EditAnywhere, Category = "ROS Subscriber")
    AActor* Owner;		
	
};
