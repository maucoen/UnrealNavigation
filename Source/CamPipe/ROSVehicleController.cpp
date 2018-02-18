// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSVehicleController.h"


// Sets default values for this component's properties
UROSVehicleController::UROSVehicleController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UROSVehicleController::BeginPlay()
{
	Super::BeginPlay();

	// ...
    // auto Root = Owner->GetRootComponent();
    // UE_LOG(LogTemp, Warning, TEXT("root worked"));
    // this->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
    // Set websocket server address to default
    Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(IPAddress, Port));

    // **** Create Subscriber here ****
	Handler->AddSubscriber(
		MakeShareable<FROSControllerSubscriberCallback>(
        new FROSControllerSubscriberCallback(Owner, Type, Topic)));

   	UE_LOG(LogTemp, Warning, TEXT("Added subscriber for control messges"));
       
    //Connect to ROSBridge Websocket server.
    Handler->Connect();
}

// Called when game ends or actor deleted
void UROSVehicleController::EndPlay(const EEndPlayReason::Type Reason)
{
    Handler->Disconnect();
    Super::EndPlay(Reason);
}

// Called every frame
void UROSVehicleController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

    if(Handler.IsValid()) Handler->Process();
}

