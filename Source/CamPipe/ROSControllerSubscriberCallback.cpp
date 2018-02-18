

#include "ROSControllerSubscriberCallback.h"


FROSControllerSubscriberCallback::FROSControllerSubscriberCallback(
	AActor* InOwner, const FString& InType, const FString& InTopic) :
	FROSBridgeSubscriber(InTopic, InType)
{
    // UE_LOG(LogTemp, Warning, TEXT("Initialised ROSControllerCallback"));
    Owner = InOwner;
}

FROSControllerSubscriberCallback::~FROSControllerSubscriberCallback()
{
}

TSharedPtr<FROSBridgeMsg> FROSControllerSubscriberCallback::ParseMessage
(TSharedPtr<FJsonObject> JsonObject) const
{
    // UE_LOG(LogTemp, Warning, TEXT("Inside Parse Message for Controller Subscriber"));
	TSharedPtr<geometry_msgs::Twist> TwistMessage =
		MakeShareable<geometry_msgs::Twist>(new geometry_msgs::Twist());
	TwistMessage->FromJson(JsonObject);
	return StaticCastSharedPtr<FROSBridgeMsg>(TwistMessage);
}

void FROSControllerSubscriberCallback::Callback(TSharedPtr<FROSBridgeMsg> Msg)
{
	TSharedPtr<geometry_msgs::Twist> TwistMessage = StaticCastSharedPtr<geometry_msgs::Twist>(Msg);
	// downcast to subclass using StaticCastSharedPtr function

	UE_LOG(LogTemp, Log, TEXT("[%s] Message received by %s!"),
		*FString(__FUNCTION__), *Owner->GetName());//, *TwistMessage->GetLinear());
	// do something with the message

    // Get messages out into an fvector
    geometry_msgs::Vector3 LinearVelocity = TwistMessage->GetLinear();
    geometry_msgs::Vector3 AngularVelocity = TwistMessage->GetAngular();

    // FVector LinearCommand = FVector(LinearVelocity.x, LinearVelocity.y, LinearVelocity.z);
    // FVector AngularCommand = FVector(AngularVelocity.x, AngularVelocity.y, AngularVelocity.z);

    UE_LOG(LogTemp,Warning, TEXT("Linear Command is %f"),LinearVelocity.GetX());

    // Send command to the vehicle 
    auto Vehicle = Cast<AWheeledVehicle>(Owner);
    Vehicle->GetVehicleMovementComponent()->SetThrottleInput(LinearVelocity.GetX());
    Vehicle->GetVehicleMovementComponent()->SetSteeringInput(-AngularVelocity.GetZ());

	return;
}

