// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"


// Sets default values
ACameraDirector::ACameraDirector()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();

	SetCameraSwitchInput();
	FindAllMovableCameraComponents(GetWorld(), Cameras);
	UE_LOG(LogTemp, Warning, TEXT("Begin Play Camera"));
}

void ACameraDirector::SetCameraSwitchInput()
{
	// Find the actor that handles control for the local player.
	Controller = UGameplayStatics::GetPlayerController(this, 0);

	if (Controller)
	{
		InputComponent = NewObject<UInputComponent>(this);
		//InputComponent->bBlockInput = bBlockInput;

		if (InputComponent)
		{
			InputComponent->BindKey(EKeys::C, EInputEvent::IE_Pressed, this, &ACameraDirector::SwitchCam);
			//InputComponent->BindAction("SwitchCamera", IE_Pressed, this, &ACameraDirector::SwitchCam);
			EnableInput(Controller);
		}
	}
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACameraDirector::SwitchCam()
{
	if (Controller && (CamIndex < ( Cameras.Num()-1)))
	{
		++CamIndex;
		Controller->SetViewTarget(Cameras[CamIndex]);
	}
	else
	{
		CamIndex = 0;
		Controller->SetViewTarget(Cameras[CamIndex]);
	}
}

template<typename T>
void ACameraDirector::FindAllMovableCameraComponents(UWorld* World, TArray<T*>& Out)
{
	for (TActorIterator<AActor> It(World, T::StaticClass()); It; ++It)
	{
		T* Actor = Cast<T>(*It);
		if (Actor->IsRootComponentMovable() && Actor && !Actor->IsPendingKill())
		{
			// add only if it has a camera component
			if (Actor->FindComponentByClass<UCameraComponent>() != NULL)
			{
				Out.Emplace(Actor);
			}
		}
	}
	//Remove last element from array, which seems to be a generic camera actor
	FString Popped = Out.Pop()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Camera Iterator: popped %s"), *Popped);
}

