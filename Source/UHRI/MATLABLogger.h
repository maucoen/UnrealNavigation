// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C://Program Files/MATLAB/R2017A/extern/include/engine.h"

#include "MATLABLogger.generated.h"

/**
 * 
 */
UCLASS()
class UHRI_API AMATLABLogger : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AMATLABLogger();

	void PostLogin(APlayerController* NewPlayer) override;

	void SendToMatlab();

	void Logout(AController* Exiting) override;

	bool bIsServer = true;

private:
	TArray<APawn*> Players;

	mxArray *T = NULL, *a = NULL, *d = NULL;
	double time[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	double *Dreal, *Dimag;

	FVector InitialPos;

	Engine *Matlab = nullptr;
};
