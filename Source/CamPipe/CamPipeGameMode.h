// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ROSBridgeHandler.h"
#include "CamPipeGameMode.generated.h"

UCLASS(MinimalAPI)
class ACamPipeGameMode : public AGameMode
{
	GENERATED_BODY()

protected:

    // Add a ROSBridgePublisher smart pointer
    TSharedPtr<FROSBridgePublisher> Publisher;

    TSharedPtr<FROSBridgeSubscriber> Subscriber;
	
	UPROPERTY(EditAnywhere)
    FString IPAddress;

    UPROPERTY(EditAnywhere)
    uint32 Port;


public:

	// Add a smart pointer to ROSBridgeHandler
    TSharedPtr<FROSBridgeHandler> Handler;

	ACamPipeGameMode();

	void InitGame(    
 	const FString & MapName,
    const FString & Options,
    FString & ErrorMessage) override;

	void PostLogin(APlayerController* NewPlayer) override;
	void Logout(AController* Exiting) override;

	void StartToLeaveMap() override;

	void Tick(float DeltaTime) override;

	void AddSubscriber(FString InTopic, FString InType);
	void AddPublisher(FString InTopic, FString InType);

};



