// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ROSBridgeHandler.h"
#include "ROSLoggerGameMode.generated.h"


UCLASS()
class CAMPIPE_API AROSLoggerGameMode : public AGameMode
{
	GENERATED_BODY()
	
protected:
    // Add a ROSBridgePublisher smart pointer
    TSharedPtr<FROSBridgePublisher> Publisher;

    TSharedPtr<FROSBridgeSubscriber> Subscriber;
	
	UPROPERTY(EditAnywhere)
    FString IPAddress = TEXT("127.0.1.1");;

    UPROPERTY(EditAnywhere)
    uint32 Port = 9090;;

	FString MapName;
	
public:
	// Add a smart pointer to ROSBridgeHandler
    TSharedPtr<FROSBridgeHandler> Handler;

	AROSLoggerGameMode();

	void StartPlay() override;

	void PostLogin(APlayerController* NewPlayer) override;
	void Logout(AController* Exiting) override;

	void StartToLeaveMap() override;

	void Tick(float DeltaTime) override;

	void AddSubscriber(FString InTopic, FString InType);
	void AddPublisher(FString InTopic, FString InType);

};
