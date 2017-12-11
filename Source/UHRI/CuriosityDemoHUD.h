// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CuriosityDemoHUD.generated.h"

/**
 * 
 */
UCLASS()
class UHRI_API ACuriosityDemoHUD : public AHUD
{
	GENERATED_BODY()
	
	
public:
	ACuriosityDemoHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	
};
