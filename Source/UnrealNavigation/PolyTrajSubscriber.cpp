    
#include "PolyTrajSubscriber.h"
#include "ROSImagePublisher.h"

#include "CoreMinimal.h"
//#include "CoordConvStatics.h"


FPolyTrajSubscriber::FPolyTrajSubscriber(
	const FString& InType, const FString& InTopic, AROSImagePublisher* InOwner) :
	FROSBridgeSubscriber(InTopic, InType)
{
    UE_LOG(LogTemp, Warning, TEXT("Initialised FPolyTrajSubscriber"));
    Owner = InOwner;
}

TSharedPtr<FROSBridgeMsg> FPolyTrajSubscriber::ParseMessage
(TSharedPtr<FJsonObject> JsonObject) const
{
    //UE_LOG(LogTemp, Warning, TEXT("Inside Parse Message for PolyTraj Subscriber"));
	TSharedPtr<px4_msgs::PolyTraj> TrajMsg =
		MakeShareable<px4_msgs::PolyTraj>(new px4_msgs::PolyTraj());
	TrajMsg->FromJson(JsonObject);
	return StaticCastSharedPtr<FROSBridgeMsg>(TrajMsg);
}

void FPolyTrajSubscriber::Callback(TSharedPtr<FROSBridgeMsg> Msg)
{
    // downcast from FROSBridge to px4_msg::PolyTraj
	TSharedPtr<px4_msgs::PolyTraj> Trajectory = StaticCastSharedPtr<px4_msgs::PolyTraj>(Msg);

    Traj = *Trajectory;
    _x_traj = polytraj::Traj(Traj.n_segs, Traj.t_trans,
                       Traj.n_x_coeffs, Traj.x_coeffs);
    _y_traj = polytraj::Traj(Traj.n_segs, Traj.t_trans,
                       Traj.n_y_coeffs, Traj.y_coeffs);
    _z_traj = polytraj::Traj(Traj.n_segs, Traj.t_trans,
                       Traj.n_z_coeffs, Traj.z_coeffs);
    _yaw_traj = polytraj::Traj(Traj.n_segs, Traj.t_trans,
                    Traj.n_yaw_coeffs, Traj.yaw_coeffs);

    // Update maximum time
    TMax = Traj.t_trans[Traj.n_segs-1];

    if (TMax < 2.0f)
    {
       UE_LOG(LogTemp,Warning, TEXT("traj is short, won't navigate"));
       bHasTraj = false; 
    }
    else
    {
        UE_LOG(LogTemp,Warning, TEXT("got new traj"));
        bHasTraj = true;
    }

    Owner->CreateSplineMesh();
    // Update replan time buffer - so trajectory is reset to zero at the new traj start
    ReplanTimeReset = LatestTime;

	return;
}

FVector FPolyTrajSubscriber::GetNewLocation(float InElapsedTime)
{
    // Record latest time
    LatestTime = InElapsedTime;

    // Adjust for replanning buffer
    InElapsedTime = InElapsedTime - ReplanTimeReset;

    // Fix to maximum if it exceeds the maximum
    if (InElapsedTime >= TMax)
    {
        InElapsedTime = TMax;
        UE_LOG(LogTemp, Warning, TEXT("EXCEEDED MAXIMUM TIME: %f, stopping at final location"),TMax);
    }

    FVector EvaluatedLocation = FVector(
        _x_traj.EvalTraj(InElapsedTime, 0)*100.0,
        -_y_traj.EvalTraj(InElapsedTime, 0)*100.0,
        _z_traj.EvalTraj(InElapsedTime, 0)*100.0);

    //UE_LOG(LogTemp, Warning, TEXT("Get new loc: %s"),*EvaluatedLocation.ToString());

    return EvaluatedLocation;
}

void FPolyTrajSubscriber::ResetReplanTimeOffset()
{
    ReplanTimeReset = 0.0f;
}
