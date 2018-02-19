// Fill out your copyright notice in the Description page of Project Settings.

#include "MarsDTMLevel.h"
#include "Kismet/GameplayStatics.h"
#include "InputCoreTypes.h"
//#include "UHRIGameInstance.h"

void AMarsDTMLevel::BeginPlay()
{
	Super::BeginPlay();

	Controller = UGameplayStatics::GetPlayerController(this, 0);

	if (Controller)
	{
		InputComponent = NewObject<UInputComponent>(this);
		if (InputComponent)
		{
	
			InputComponent->BindKey(EKeys::Escape, EInputEvent::IE_Pressed, this, &AMarsDTMLevel::InLoadMenu);
		}
	}
}
void AMarsDTMLevel::InLoadMenu()
{
	//auto GameInstance = Cast<UUHRIGameInstance, UGameInstance>(GetGameInstance());
	//GameInstance->InGameLoadMenu();
}
