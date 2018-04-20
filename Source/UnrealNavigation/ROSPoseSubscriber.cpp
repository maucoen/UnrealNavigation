    
#include "ROSPoseSubscriber.h"
#include "geometry_msgs/PoseStamped.h"
#include "ROSImagePublisher.h"
#include "CoordConvStatics.h"


FROSPoseSubscriber::FROSPoseSubscriber(
	const FString& InType, const FString& InTopic) :
	FROSBridgeSubscriber(InTopic, InType)
{
    UE_LOG(LogTemp, Warning, TEXT("Initialised FROSPoseSubscriber"));
    //Owner = InOwner;
}

TSharedPtr<FROSBridgeMsg> FROSPoseSubscriber::ParseMessage
(TSharedPtr<FJsonObject> JsonObject) const
{
    UE_LOG(LogTemp, Warning, TEXT("Inside Parse Message for Controller Subscriber"));
	TSharedPtr<geometry_msgs::PoseStamped> Pose =
		MakeShareable<geometry_msgs::PoseStamped>(new geometry_msgs::PoseStamped());
	Pose->FromJson(JsonObject);
	return StaticCastSharedPtr<FROSBridgeMsg>(Pose);
}

void FROSPoseSubscriber::Callback(TSharedPtr<FROSBridgeMsg> Msg)
{
    //UE_LOG(LogTemp,Warning, TEXT("inside callback"));

	TSharedPtr<geometry_msgs::PoseStamped> Pose = StaticCastSharedPtr<geometry_msgs::PoseStamped>(Msg);
	// downcast to subclass using StaticCastSharedPtr function

    // Get messages out into an fvector
    geometry_msgs::Point NewPoint = Pose->GetPose().GetPosition();

    FVector newpoint = NewPoint.GetVector();
    point = FCoordConvStatics::ROSToU(newpoint);
    
    UE_LOG(LogTemp,Warning, TEXT("got point %s"),*point.ToString());

    // //constructs and sets transform based on identity quat, Setpoint and scale 1
    // State = FTransform();
    // State.SetLocation(Setpoint);
    // State.SetTranslation(Setpoint);

    // UE_LOG(LogTemp,Warning, TEXT("got pose l %s"),*State.GetLocation().ToString());
    // UE_LOG(LogTemp,Warning, TEXT("got pose t %s"),*State.GetTranslation().ToString());

	return;
}

//FTransform GetState() {return State;}