    
#include "ROSPoseSubscriber.h"
#include "geometry_msgs/PoseStamped.h"
#include "ROSImagePublisher.h"


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

	// UE_LOG(LogTemp, Log, TEXT("[%s] Message received by %s!"),
	// 	*FString(__FUNCTION__), *Owner->GetName());//, *Pose->GetLinear());
	// // do something with the message

    // Get messages out into an fvector
    geometry_msgs::Point NewPoint = Pose->GetPose().GetPosition();

    //UE_LOG(LogTemp,Warning, TEXT("got point %s"),*State.GetTranslation().ToString());

    NewPoint.SetVector(Point); //out param

    Point = {(float)NewPoint.GetX(), (float)NewPoint.GetY(), (float)NewPoint.GetZ()};

    UE_LOG(LogTemp,Warning, TEXT("got point %s"),*Point.ToString());

    // //constructs and sets transform based on identity quat, Setpoint and scale 1
    // State = FTransform();
    // State.SetLocation(Setpoint);
    // State.SetTranslation(Setpoint);

    // UE_LOG(LogTemp,Warning, TEXT("got pose l %s"),*State.GetLocation().ToString());
    // UE_LOG(LogTemp,Warning, TEXT("got pose t %s"),*State.GetTranslation().ToString());

	return;
}

//FTransform GetState() {return State;}