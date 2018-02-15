// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSLoggerSimState.h"
#include "CamPipeGameMode.h"
#include "ROSBridgeHandler.h"
#include "geometry_msgs/Transform.h"
#include "CoordConvStatics.h"

void AROSLoggerSimState::AddPublisher(const FString& InTopic, const FString& InType)
{
    auto* mymode= Cast<ACamPipeGameMode>(GetWorld()->GetAuthGameMode());
    mymode->AddPublisher(InTopic, InType);
}

void AROSLoggerSimState::AddSubscriber(const FString& InTopic, const FString& InType)
{
    auto* mymode= Cast<ACamPipeGameMode>(GetWorld()->GetAuthGameMode());
    mymode->AddSubscriber(InTopic, InType);
}


void AROSLoggerSimState::PublishTransform(const FString& InTopic, const FTransform InTF)
{
    FTransform TF = FCoordConvStatics::UToROS(InTF);
    FVector tr = TF.GetTranslation();
	FQuat qt = TF.GetRotation();

    //Construct geometry::msg transfrom
	//geometry::msgs Vector3, Quaternion already have
	//overloaded constructors from FVector
    TSharedPtr<geometry_msgs::Transform> TransformToSend = MakeShareable(
       new geometry_msgs::Transform(geometry_msgs::Vector3(tr), 
                                    geometry_msgs::Quaternion(qt)));

    auto* mymode= Cast<ACamPipeGameMode>(GetWorld()->GetAuthGameMode());
    mymode->Handler->PublishMsg(InTopic, TransformToSend);
}
// bool AROSLoggerSimState::Server_AddPublisher_Validate(const FString& InTopic, const FString& InType)
// {
//     return true;
// }

// void AROSLoggerSimState::Server_PublishTransform_Validate(const FTransform InTF)
// {
//     return true;
// }

// bool AROSLoggerSimState::Server_AddSubscriber_Validate(const FString& InTopic, const FString& InType)
// {
//     return true;
// }

// void AROSLoggerSimState::Server_Publish_Implementation(const FString& InTopic, const TSharedPtr<FROSBridgeMsg> InMsg)
// {
//     AMyGameMode * mymode= Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
//     mymode->Publish(InTopic, InMsg);
// }

// bool AROSLoggerSimState::Server_Publish_Validate(const FString& InTopic, const TSharedPtr<FROSBridgeMsg> InMsg)
// {
//     return true;
// }