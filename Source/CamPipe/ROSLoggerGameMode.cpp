// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSLoggerGameMode.h"
#include "ROSLoggerSimState.h"
#include "CamPipePawn.h"
#include "CamPipeHud.h"

AROSLoggerGameMode::AROSLoggerGameMode()
{
	//DefaultPawnClass = ACamPipePawn::StaticClass();
	HUDClass = ACamPipeHud::StaticClass();
	//GameStateClass = AROSLoggerSimState::StaticClass();
	PrimaryActorTick.bCanEverTick = true;

    UE_LOG(LogTemp, Warning, TEXT("GameMode:cotr"));
}

void AROSLoggerGameMode::StartPlay()
{
    UE_LOG(LogTemp, Warning, TEXT("GameMode: about to start"));

    MapName = GetWorld()->GetMapName();
	if((MapName != TEXT("MainMenu")) && !Handler.IsValid())
    {
	    // Set websocket server address to default
       // Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(IPAddress, Port));
        
	UE_LOG(LogTemp, Warning, TEXT("GameMode: bridge shareable"));

        //Connect to ROSBridge Websocket server.
   // Handler->Connect();
        
	UE_LOG(LogTemp, Warning, TEXT("GameMode: bridge connected"));

    }
}

void AROSLoggerGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogTemp, Warning, TEXT("GameMode: Posted login for new player"));
}

void AROSLoggerGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

    
	UE_LOG(LogTemp, Warning, TEXT("GameMode: LOGOUT"));


    if (NumPlayers < 1 && Handler.IsValid()) Handler->Disconnect();
}

void AROSLoggerGameMode::StartToLeaveMap()
{
	if (Handler.IsValid())
	{
	    Handler->Disconnect();
	}
	Super::StartToLeaveMap();
}

void AROSLoggerGameMode::AddPublisher(FString InTopic, FString InType)
{
	// **** Create publishers here ****
	Handler->AddPublisher(
     	MakeShareable<FROSBridgePublisher>(
         new FROSBridgePublisher(InTopic, InType)));
}

void AROSLoggerGameMode::AddSubscriber(FString InTopic, FString InType)
{
	// **** Create subs here ****
//    Handler->AddSubscriber(
// 		MakeShareable<FROSBridgeSubscriber>(
//         new FROSBridgeSubscriber(InTopic, InType)));
}

//void AROSLoggerGameMode::Publish(FString InTopic, TSharedPtr<FROSBridgeMsg> InMsg)
//{
	// **** Create subs here ****
   //	Handler->PublishMsg(InTopic, InMsg);
    //UE_LOG(LogTemp, Log, TEXT("sent image to ROS: %s"), *tr.ToString());
//}

void AROSLoggerGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Handler.IsValid())
	{
	    Handler->Process();
	}

    
}






