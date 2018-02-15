// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CamPipeGameMode.h"
#include "CamPipePawn.h"
#include "CamPipeHud.h"
#include "ROSLoggerSimState.h"
//#include "ROSBridgePublisher.h"
//#include "ROSBridgeSubscriber.h"
#include "ROSBridgeHandler.h"

ACamPipeGameMode::ACamPipeGameMode()
{
	DefaultPawnClass = ACamPipePawn::StaticClass();
	HUDClass = ACamPipeHud::StaticClass();
	//GameStateClass = AROSLoggerSimState::StaticClass();

	PrimaryActorTick.bCanEverTick = true;

	// Set websocket server address to the ros IP address
    IPAddress = TEXT("127.0.1.1");
    // Set Port to 9090
    Port = 9090;
}

void ACamPipeGameMode::InitGame(    
 	const FString & MapName,
    const FString & Options,
    FString & ErrorMessage)
{

	// if((MapName!= TEXT("Main Menu")) && !Handler.IsValid())
	// {
		
	// 	// Set websocket server address to default
    // 	Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(IPAddress, Port));

    // 	//Connect to ROSBridge Websocket server.
    // 	Handler->Connect();
	// }
}

void ACamPipeGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	//++NumberOfPlayers;

	UE_LOG(LogTemp, Warning, TEXT("GameMode: Posted login for new player"));
}


void ACamPipeGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	//--NumberOfPlayers;
}

void ACamPipeGameMode::StartToLeaveMap()
{
	// if (Handler.IsValid())
	// {
	// 	Handler->Disconnect();
	// }

	Super::StartToLeaveMap();
}

void ACamPipeGameMode::AddPublisher(FString InTopic, FString InType)
{
	// **** Create publishers here ****
	// Handler->AddPublisher(
	// 	MakeShareable<FROSBridgePublisher>(
    //     new FROSBridgePublisher(InTopic, InType)));
}

void ACamPipeGameMode::AddSubscriber(FString InTopic, FString InType)
{
	// **** Create subs here ****
//    Handler->AddSubscriber(
// 		MakeShareable<FROSBridgeSubscriber>(
//         new FROSBridgeSubscriber(InTopic, InType)));
}

//void ACamPipeGameMode::Publish(FString InTopic, TSharedPtr<FROSBridgeMsg> InMsg)
//{
	// **** Create subs here ****
   //	Handler->PublishMsg(InTopic, InMsg);
    //UE_LOG(LogTemp, Log, TEXT("sent image to ROS: %s"), *tr.ToString());
//}

void ACamPipeGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if (Handler.IsValid())
	// {
	// 		Handler->Process();
	// }
}


