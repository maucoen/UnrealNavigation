    
#include "PolyTrajSubscriber.h"
#include "ROSImagePublisher.h"
#include "Components/SplineComponent.h"
//#include "CoordConvStatics.h"


FPolyTrajSubscriber::FPolyTrajSubscriber(
	const FString& InType, const FString& InTopic) :
	FROSBridgeSubscriber(InTopic, InType)
{
    UE_LOG(LogTemp, Warning, TEXT("Initialised FPolyTrajSubscriber"));
    //Owner = InOwner;

    Spline = NewObject<USplineComponent>();
    Spline->SetDrawDebug(true);
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
    //UE_LOG(LogTemp,Warning, TEXT("inside polyraj callback"));

	TSharedPtr<px4_msgs::PolyTraj> Trajectory = StaticCastSharedPtr<px4_msgs::PolyTraj>(Msg);
	// downcast to subclass using StaticCastSharedPtr function

    Traj = *Trajectory;
    _x_traj = polytraj::Traj(Traj.n_segs, Traj.t_trans,
                       Traj.n_x_coeffs, Traj.x_coeffs);
    _y_traj = polytraj::Traj(Traj.n_segs, Traj.t_trans,
                       Traj.n_y_coeffs, Traj.y_coeffs);
    _z_traj = polytraj::Traj(Traj.n_segs, Traj.t_trans,
                       Traj.n_z_coeffs, Traj.z_coeffs);
    _yaw_traj = polytraj::Traj(Traj.n_segs, Traj.t_trans,
                    Traj.n_yaw_coeffs, Traj.yaw_coeffs);

<<<<<<< HEAD
    float tmax = 1.5f;
    Spline->ClearSplinePoints();
    for(float i = 0.0f; i<tmax; i++)
    {
        Spline->AddPoint(
            FSplinePoint(
                i,
                FVector(
                    _x_traj.EvalTraj(i*10, 0)*100.0,
                    -_y_traj.EvalTraj(i*10, 0)*100.0,
                    _z_traj.EvalTraj(i*10, 0)*100.0)
            )
        );
        UE_LOG(LogTemp,Warning, TEXT("evaled %d"), i);
    }
     
    UE_LOG(LogTemp,Warning, TEXT("got new traj"));
    bHasTraj = true;

=======
    
    // Update maximum time
    TMax = Traj.t_trans[Traj.n_segs-1];

    UE_LOG(LogTemp,Warning, TEXT("got new traj"));
    bHasTraj = true;

    // Update replan time buffer - so trajectory is reset to zero at the new traj start
    ReplanTimeReset = LatestTime;
 
>>>>>>> c812386a8044d8c680dc86318b7e7f719f243ce8
	return;
}

FVector FPolyTrajSubscriber::GetNewLocation(float InElapsedTime)
{
    // Record latest time
    LatestTime = InElapsedTime;

    // Adjust for replanning buffer
    InElapsedTime = InElapsedTime - ReplanTimeReset;

    // Fix to maximum if it exceeds the maximum
    if (InElapsedTime > TMax){
        InElapsedTime = TMax;
        UE_LOG(LogTemp, Warning, TEXT("EXCEEDED MAXIMUM TIME: %f, stopping at final location"),TMax);
    }
    
    FVector EvaluatedLocation = FVector(
        _x_traj.EvalTraj(InElapsedTime, 0)*100.0,
        -_y_traj.EvalTraj(InElapsedTime, 0)*100.0,
        _z_traj.EvalTraj(InElapsedTime, 0)*100.0);

    UE_LOG(LogTemp, Warning, TEXT("FVector location is: (%f, %f, %f)"),_x_traj.EvalTraj(InElapsedTime, 0),_y_traj.EvalTraj(InElapsedTime, 0),_z_traj.EvalTraj(InElapsedTime, 0));

    return EvaluatedLocation;
    

}

void FPolyTrajSubscriber::ResetReplanTimeOffset(){
    ReplanTimeReset = 0.0;
}