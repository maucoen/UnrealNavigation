// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ROSLoggerSimState.generated.h"

/**
 * 
 */
UCLASS()
class CAMPIPE_API AROSLoggerSimState : public AGameStateBase
{
	GENERATED_BODY()
	
	public:

	void AddSubscriber(const FString& InTopic, const FString& InType);

	void AddPublisher(const FString& InTopic, const FString& InType);

    void PublishTransform(const FString& InTopic, const FTransform InTF);


};
