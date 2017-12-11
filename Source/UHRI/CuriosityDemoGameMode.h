// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CuriosityDemoGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UHRI_API ACuriosityDemoGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	ACuriosityDemoGameMode();


private:
	TSubclassOf<class UUserWidget> InputListClass;
	class UUserWidget* InputList;

	void ToggleViewport();

	virtual void StartPlay() override;

	bool bDraw = false;

};
