// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UHRIGameMode.generated.h"

UCLASS(minimalapi)
class AUHRIGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AUHRIGameMode();

	void PostLogin(APlayerController* NewPlayer) override;

	void TimerRep();

	void Logout(AController* Exiting) override;

	bool bIsServer = true;

private:
	TArray<APlayerController*> Players;
};
