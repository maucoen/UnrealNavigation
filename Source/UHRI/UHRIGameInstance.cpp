// Fill out your copyright notice in the Description page of Project Settings.

#include "UHRIGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "GameLiftClientSDK/Public/GameLiftClientObject.h"
#include "GameLiftClientSDK/Public/GameLiftClientApi.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"
#include "TimerManager.h"

const static FName SESSION_NAME = TEXT("Game");
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("ServerName");
const static FString ACCESS_KEY = "AKIAJXN6HZA3XIEZHTQQ";
const static FString SECRET_KEY = "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";

UUHRIGameInstance::UUHRIGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;
	InGameMenuClass = InGameMenuBPClass.Class;

	
	
	
}

void UUHRIGameInstance::Init()
{
	Super::Init();

	// Create the game lift object. This is required before calling any GameLift functions.
	GameLiftClientObject = UGameLiftClientObject::CreateGameLiftObject(ACCESS_KEY, SECRET_KEY, "us-east-1", true, 8080);
	////////////////////

	Subsystem = IOnlineSubsystem::Get();
	
	if (Subsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found OSS %s"), *Subsystem->GetSubsystemName().ToString());
		SessionInterface = Subsystem->GetSessionInterface(); //shared pointer

		if (SessionInterface.IsValid())  //shared pointer
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UUHRIGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UUHRIGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UUHRIGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UUHRIGameInstance::OnJoinSessionComplete);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found NO OSS"));
	}

	FTimerHandle GameStartTimer;
	GetTimerManager().SetTimer(GameStartTimer, this, &UUHRIGameInstance::WeHaveAPawn, 1.0f, true, 2.0f);
}

// Blueprint callable 
void UUHRIGameInstance::LoadMenuWidget()
{
	if (!ensure(MenuClass != nullptr)) return;

	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();

	Menu->SetMenuInterface(this);
}

void UUHRIGameInstance::InGameLoadMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;

	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();

	Menu->SetMenuInterface(this);

	if (Subsystem->IsServer())
	{
		UE_LOG(LogTemp, Warning, TEXT("I am a server!"));
	}
	if (Subsystem->IsDedicated())
	{
		UE_LOG(LogTemp, Warning, TEXT("I am dedicated!"));
	}
	else if(!Subsystem->IsServer())
	{
		UE_LOG(LogTemp, Warning, TEXT("I am client!"));
	}
}

void UUHRIGameInstance::Host(FString ServerName)
{

	DesiredServerName = ServerName;
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);

		UE_LOG(LogTemp, Warning, TEXT("Found existing session"));

		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME); //will create session after destroy session complete
			UE_LOG(LogTemp, Warning, TEXT("Destroying session "));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("About to create session"));
			CreateSession();
		}
	}
}

void UUHRIGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldnt create session"));
		return;
	}
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Maps/GaleCrater?listen");
}

void UUHRIGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	UE_LOG(LogTemp, Warning, TEXT("Inside Destroy session complete"));
	if (Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inside success of destroycomplete"));
		CreateSession();
	}
}

void UUHRIGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{

		FOnlineSessionSettings SessionSettings;

		if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
		{
			SessionSettings.bIsLANMatch = true;
		}
		else
		{
			SessionSettings.bIsLANMatch = false;
		}

		SessionSettings.NumPublicConnections = 5;
		SessionSettings.bShouldAdvertise = true; //to be searchable and findable
		SessionSettings.bUsesPresence = true;
		SessionSettings.Set(SERVER_NAME_SETTINGS_KEY, DesiredServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UUHRIGameInstance::Join(uint32 Index)
{
	if (!SessionInterface.IsValid() || !SessionSearch.IsValid()) return;
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
}

void UUHRIGameInstance::StartSession()
{
	if (SessionInterface.IsValid())
	{
		SessionInterface->StartSession(SESSION_NAME);
	}
}

void UUHRIGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid()) return;

	switch (Result)
	{
		case EOnJoinSessionCompleteResult::Type::Success:
		{
			FString Address;
			if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
			{
				UE_LOG(LogTemp, Warning, TEXT("Couldnt find connection string"));
			}

			UEngine* Engine = GetEngine();
			if (!ensure(Engine != nullptr)) return;

			Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

			APlayerController* PlayerController = GetFirstLocalPlayerController();
			if (!ensure(PlayerController != nullptr)) return;

			PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
		}
		case EOnJoinSessionCompleteResult::Type::SessionIsFull:
		{
			UE_LOG(LogTemp, Warning, TEXT("Session Full"));
		}
		case EOnJoinSessionCompleteResult::Type::UnknownError:
		{
			UE_LOG(LogTemp, Warning, TEXT("Unkown Error"));
		}
		case EOnJoinSessionCompleteResult::Type::SessionDoesNotExist:
		{
			UE_LOG(LogTemp, Warning, TEXT("Session does not exist"));
		}
		case EOnJoinSessionCompleteResult::Type::CouldNotRetrieveAddress:
		{
			UE_LOG(LogTemp, Warning, TEXT("Couldnt retrieve address"));
		}
		case EOnJoinSessionCompleteResult::Type::AlreadyInSession:
		{
			UE_LOG(LogTemp, Warning, TEXT("Already in Session!"));
		}
	}
}

void UUHRIGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UUHRIGameInstance::RequestServerList()
{
	//SessionSearch = MakeShareable(new FOnlineSessionSearch());  //new allocates heap instead of stack, mksh changes to shrd ptr

	//if (SessionSearch.IsValid())
	//{
	//	->bIsLanQuery = true;
	//	SessionSearch->MaxSearchResults = 100;
	//	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals); //for Server side queries
	//	UE_LOG(LogTemp, Warning, TEXT("Starting FindSession"));
	//	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	//}
	CreateGameSession();
}

void UUHRIGameInstance::OnFindSessionsComplete(bool Sucess)
{
	if (Sucess && SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Completed FindSessions"));
		TArray<FServerData> ServerList;

		//ServerList = { "Server1", "Server2" , "Server3" }; for testing only

		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults) // or auto& SearchResults :
		{
			FServerData Data;
			Data.Name = SearchResult.GetSessionIdStr();
			Data.HostUsername = SearchResult.Session.OwningUserName;
			Data.MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
			Data.CurrentPlayers = Data.MaxPlayers - SearchResult.Session.NumOpenPublicConnections;

			FString ServerName;
			if (SearchResult.Session.SessionSettings.Get(SERVER_NAME_SETTINGS_KEY, ServerName))
			{
				UE_LOG(LogTemp, Warning, TEXT("Data found in settings %s"), *ServerName);
				Data.Name = ServerName;
			}
			else
			{
				Data.Name = "Could not get name";
			}
			ServerList.Add(Data);
		}
		if (Menu != nullptr)
		{
			Menu->SetServerList(ServerList);
		}
	}
}


/// GAMELIFT SPECIFIC FUNCTIONS
void UUHRIGameInstance::CreateGameSession()
{
 
	FGameLiftGameSessionConfig MySessionConfig;
	MySessionConfig.SetAliasID("Your Alias ID");
	MySessionConfig.SetMaxPlayers(10);
	UGameLiftCreateGameSession* MyGameSessionObject = GameLiftClientObject->CreateGameSession(MySessionConfig);
	MyGameSessionObject->OnCreateGameSessionSuccess.AddDynamic(this, &UUHRIGameInstance::OnGameCreationSuccess);
	MyGameSessionObject->OnCreateGameSessionFailed.AddDynamic(this, &UUHRIGameInstance::OnGameCreationFailed);
	MyGameSessionObject->Activate();
 
}

void UUHRIGameInstance::OnGameCreationSuccess(const FString& GameSessionID)
{
	DescribeGameSession(GameSessionID);
}

void UUHRIGameInstance::OnGameCreationFailed(const FString& ErrorMessage)
{
 
	// Do stuff...
 
}

void UUHRIGameInstance::DescribeGameSession(const FString& GameSessionID)
{
 
	/*UGameLiftDescribeGameSession* MyDescribeGameSessionObject = GameLiftClientObject->DescribeGameSession(GameSessionID);
	MyDescribeGameSessionObject->OnDescribeGameSessionStateSuccess.AddDynamic(this, &UUHRIGameInstance::OnDescribeGameSessionSuccess);
	MyDescribeGameSessionObject->OnDescribeGameSessionStateFailed.AddDynamic(this, &UUHRIGameInstance::OnDescribeGameSessionFailed);
	MyDescribeGameSessionObject->Activate();
*/
	
	CreatePlayerSession(GameSessionID, "Your Unique Player ID");
 
}

void UUHRIGameInstance::OnDescribeGameSessionSuccess(const FString& SessionID, EGameLiftGameSessionStatus SessionState)
{
	// Player sessions can only be created on ACTIVE instance.
	/*if (SessionState == EGameLiftGameSessionStatus::STATUS_Active)
	{
		CreatePlayerSession(SessionID, "Your Unique Player ID");
	}*/
}

void UUHRIGameInstance::OnDescribeGameSessionFailed(const FString& ErrorMessage)
{
 
	// Do stuff...
 
}

void UUHRIGameInstance::CreatePlayerSession(const FString& GameSessionID, const FString UniquePlayerID)
{
 
	UGameLiftCreatePlayerSession* MyCreatePlayerSessionObject = GameLiftClientObject->CreatePlayerSession(GameSessionID, UniquePlayerID);
	MyCreatePlayerSessionObject->OnCreatePlayerSessionSuccess.AddDynamic(this, &UUHRIGameInstance::OnPlayerSessionCreateSuccess);
	MyCreatePlayerSessionObject->OnCreatePlayerSessionFailed.AddDynamic(this, &UUHRIGameInstance::OnPlayerSessionCreateFail);
	MyCreatePlayerSessionObject->Activate();
 
}

void UUHRIGameInstance::OnPlayerSessionCreateSuccess(const FString& IPAddress, const FString& Port, const FString& PlayerSessionID)
{
 
	const FString TravelURL = IPAddress + ":" + Port;
//	UGameplayStatics::GetPlayerController(this, 0)->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *TravelURL));


	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);

}

void UUHRIGameInstance::OnPlayerSessionCreateFail(const FString& ErrorMessage)
{
 
	// Do stuff...
 
}

void UUHRIGameInstance::WeHaveAPawn()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if (!IsRunningDedicatedServer())
	{
		if (PlayerController)
		{
			auto pawn = PlayerController->GetControlledPawn();

			if (pawn)
			{

				//UE_LOG(LogTemp, Warning, TEXT("Yes pawn, id: %i"), pawn->GetUniqueID());
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("Yes controller, no pawn"));
			}

			auto ackpawn = PlayerController->AcknowledgedPawn;

			if (ackpawn)
			{

				//UE_LOG(LogTemp, Warning, TEXT("Yes ackpawn, id: %i"), ackpawn->GetUniqueID());
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("Yes controller, no ackpawn"));
			}

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No local controller"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("dedicated server"));

	}
}