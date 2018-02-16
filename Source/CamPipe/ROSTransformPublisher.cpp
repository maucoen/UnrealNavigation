// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSTransformPublisher.h"
#include "TimerManager.h"
#include "ROSLoggerSimState.h"



// Sets default values for this component's properties
UROSTransformPublisher::UROSTransformPublisher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    // Set rostopic name which publish strings
    //Topic = TEXT("BuggyTransform");
    //Type = TEXT("geometry_msgs/Transform");

    Owner = GetOwner();
}


// Called when the game starts
void UROSTransformPublisher::BeginPlay()
{
	Super::BeginPlay();

    auto World = Owner->GetWorld();

    auto MyGameState = World != NULL ? World->GetGameState<AROSLoggerSimState>() : NULL;
    GameState = MyGameState;

    //bind timer to server instances of publisher only
    if (GetOwnerRole()==ROLE_Authority && GameState !=NULL)
    {
        //Cast<AROSLoggerSimState>(GetGameState())->AddPublisher(Topic, Type)
        //GameState->AddPublisher(Topic, Type);
        FTimerHandle GameStartTimer;
	    Owner->GetWorldTimerManager().SetTimer(GameStartTimer, this, 
	    &UROSTransformPublisher::SendToROS, 0.2f, true, 5.0f);

    }
 }

// Called when game ends or actor deleted
void UROSTransformPublisher::EndPlay(const EEndPlayReason::Type Reason)
{
    Super::EndPlay(Reason);
}

// Called every frame
void UROSTransformPublisher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
}

void UROSTransformPublisher::SendToROS()
{
	// Transform to ROS coordinate system
    FTransform TF = Owner->GetActorTransform();
    //Send tf to gamestate
    //GameState->PublishTransform(Topic,TF);
}
