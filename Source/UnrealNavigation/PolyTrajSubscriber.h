// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROSBridgeHandler.h"
#include "ROSBridgeSubscriber.h"
#include "px4_msgs/PolyTraj.h"
#include "poly.hpp"
#include "traj.hpp"


class UNREALNAVIGATION_API FPolyTrajSubscriber : public FROSBridgeSubscriber 
{
public:
	//AROSImagePublisher* Owner;
	FPolyTrajSubscriber(const FString& InType, const FString& InTopic);//, const AROSImagePublisher* InOwner);
	TSharedPtr<FROSBridgeMsg> ParseMessage(TSharedPtr<FJsonObject> JsonObject) const override;
	void Callback(TSharedPtr<FROSBridgeMsg> Msg) override;

    px4_msgs::PolyTraj GetTrajectory() {return Traj;};
    
    FVector GetNewLocation(float InElapsedTime);

	float GetTMax(){ return TMax;};

	bool DoWeHaveTraj(){ return bHasTraj;};
	void ResetReplanTimeOffset();



protected:
	px4_msgs::PolyTraj Traj;
    polytraj::Traj _x_traj;
	polytraj::Traj _y_traj;
	polytraj::Traj _z_traj;
	polytraj::Traj _yaw_traj;

	bool bHasTraj = false;
	float TMax = 0.0f;
	float ReplanTimeReset = 0.0f;
	float LatestTime = 0.0f;
};