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

<<<<<<< HEAD
	bool DoWeHaveTraj(){ return bHasTraj;};
=======
	void ResetReplanTimeOffset();

    bool bHasTraj = false;
>>>>>>> c812386a8044d8c680dc86318b7e7f719f243ce8

private:

	px4_msgs::PolyTraj Traj;

    polytraj::Traj _x_traj;
	polytraj::Traj _y_traj;
	polytraj::Traj _z_traj;
	polytraj::Traj _yaw_traj;

<<<<<<< HEAD
	UPROPERTY()
    class USplineComponent* Spline;

	bool bHasTraj = false;
=======
	float TMax;
	float ReplanTimeReset;
	float LatestTime;
>>>>>>> c812386a8044d8c680dc86318b7e7f719f243ce8

};