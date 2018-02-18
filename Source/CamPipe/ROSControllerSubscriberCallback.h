// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROSBridgeHandler.h"
#include "ROSBridgeSubscriber.h"
#include "WheeledVehicle.h"
#include "WheeledVehicleMovementComponent.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"


class CAMPIPE_API FROSControllerSubscriberCallback : public FROSBridgeSubscriber 
{
public:
	AActor* Owner;
	FROSControllerSubscriberCallback(AActor* InOwner, const FString& InType, const FString& InTopic);
	~FROSControllerSubscriberCallback() override;
	TSharedPtr<FROSBridgeMsg> ParseMessage(TSharedPtr<FJsonObject> JsonObject) const override;
	void Callback(TSharedPtr<FROSBridgeMsg> Msg) override;
// private:
};

