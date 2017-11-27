// Fill out your copyright notice in the Description page of Project Settings.

#include "UHRIGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

//#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"

const static FName SESSION_NAME = TEXT("Game"); //named Game because of bug in NULL OSS
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("ServerName");

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
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();

	
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
}

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

	//World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	World->ServerTravel("/Game/Maps/Lobby?listen");
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
	SessionSearch = MakeShareable(new FOnlineSessionSearch());  //new allocates heap instead of stack, mksh changes to shrd ptr

	if (SessionSearch.IsValid())
	{
		//->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals); //for Server side queries
		UE_LOG(LogTemp, Warning, TEXT("Starting FindSession"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
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