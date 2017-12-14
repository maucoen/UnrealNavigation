// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MarsBuggyHUD.generated.h"

/**
 * 
 */
UCLASS()
class UHRI_API AMarsBuggyHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMarsBuggyHUD();

	/** Font used to render the vehicle info */
	UPROPERTY()
		UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface

	
	
	
};
