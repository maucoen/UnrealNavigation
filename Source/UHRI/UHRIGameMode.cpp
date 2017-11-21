// Fill out your copyright notice in the Description page of Project Settings.

#include "UHRIGameMode.h"
#include "TimerManager.h"
#include "UHRICharacter.h"
#include "UHRIGameInstance.h"
#include "UObject/ConstructorHelpers.h"


AUHRIGameMode::AUHRIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
void AUHRIGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	++NumberOfPlayers;

	if (NumberOfPlayers >= 2)
	{
		GetWorldTimerManager().SetTimer(GameStartTimer, this, &AUHRIGameMode::StartGame, 6);
	}
}
void AUHRIGameMode::StartGame()
{/*
	auto GameInstance = Cast<UUHRIGameInstance>(GetGameInstance());
	if (GameInstance == nullptr) return;

	GameInstance->StartSession();
*/
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/Maps/FirstPersonExampleMap?listen");

}
void AUHRIGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	--NumberOfPlayers;
}

