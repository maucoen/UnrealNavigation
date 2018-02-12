// Fill out your copyright notice in the Description page of Project Settings.


#include "CamPublisher.h"
#include "geometry_msgs/Transform.h"



// Sets default values
ACamPublisher::ACamPublisher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Set websocket server address to the ros IP address
    IPAddress = TEXT("127.0.1.1");

    // Set Port to 9090
    Port = 9090;

    // Set rostopic name which publish strings
    Topic = TEXT("transform");

}

// Called when the game starts or when spawned
void ACamPublisher::BeginPlay()
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
}

// Called when game ends or actor deleted
void ACamPublisher::EndPlay(const EEndPlayReason::Type Reason)
{
    // Disconnect the handler before parent ends
    Handler->Disconnect();
    Super::EndPlay(Reason);
}

// Called every frame
void ACamPublisher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Process messages
    Handler->Process();

}
