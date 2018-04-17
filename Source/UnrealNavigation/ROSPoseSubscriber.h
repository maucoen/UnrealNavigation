// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROSBridgeHandler.h"
#include "ROSBridgeSubscriber.h"


class UNREALNAVIGATION_API FROSPoseSubscriber : public FROSBridgeSubscriber 
{
public:
	//AROSImagePublisher* Owner;
	FROSPoseSubscriber(const FString& InType, const FString& InTopic);
	TSharedPtr<FROSBridgeMsg> ParseMessage(TSharedPtr<FJsonObject> JsonObject) const override;
	void Callback(TSharedPtr<FROSBridgeMsg> Msg) override;

	FTransform GetState();
	FTransform State = FTransform();
	FVector Point;

private:



};