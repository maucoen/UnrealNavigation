// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSTransformPublisher.h"
#include "geometry_msgs/Transform.h"
#include "TimerManager.h"



// Sets default values for this component's properties
UROSTransformPublisher::UROSTransformPublisher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set websocket server address to the ros IP address
    IPAddress = TEXT("127.0.1.1");

    // Set Port to 9090
    Port = 9090;

    // Set rostopic name which publish strings
    Topic = TEXT("BuggyTransform");

	Owner = GetOwner();
}


// Called when the game starts
void UROSTransformPublisher::BeginPlay()
{
	Super::BeginPlay();

	// Set websocket server address to default
    Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(IPAddress, Port));

    //Connect to ROSBridge Websocket server.
    Handler->Connect();

    // **** Create publishers here ****
    Publisher = MakeShareable<FROSBridgePublisher>(
         new FROSBridgePublisher(Topic, TEXT("geometry_msgs/Transform")));
    Handler->AddPublisher(Publisher);

    FTimerHandle GameStartTimer;
	Owner->GetWorldTimerManager().SetTimer(GameStartTimer, this, 
	&UROSTransformPublisher::SendToROS, 0.2f, true, 5.0f);
}

// Called when game ends or actor deleted
void UROSTransformPublisher::EndPlay(const EEndPlayReason::Type Reason)
{
    // Disconnect the handler before parent ends
    Handler->Disconnect();
    Super::EndPlay(Reason);
}


// Called every frame
void UROSTransformPublisher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Handler->Process();	
}

void UROSTransformPublisher::SendToROS()
{

    FTransform TF = Owner->GetActorTransform();

	FVector tr = TF.GetTranslation();
	FQuat qt = TF.GetRotation();

    // Construct geometry::msg transfrom
	// geometry::msgs Vector3, Quaternion already have
	// overloaded constructors from FVector
    TSharedPtr<geometry_msgs::Transform> FTransform = MakeShareable(
        new geometry_msgs::Transform(tr, qt));

    // Send msg to ROS
    Handler->PublishMsg(Topic, FTransform);
    UE_LOG(LogTemp, Log, TEXT("sent transform to ROS: %s"), *tr.ToString());

}
