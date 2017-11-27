// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"


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

	// Find the actor that handles control for the local player.
	Controller = UGameplayStatics::GetPlayerController(this, 0);

	if (Controller)
	{
		InputComponent = ConstructObject<UInputComponent>(UInputComponent::StaticClass(), this, "Input Component");
		InputComponent->bBlockInput = bBlockInput;

		if (InputComponent)
		{
			FindAllMovableActors(GetWorld(), Cameras);
			
			InputComponent->BindAction("SwitchCamera", IE_Pressed, this, &ACameraDirector::SwitchCam);
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
	if (Controller && Cameras.IsValidIndex(CamIndex) && (Cameras[CamIndex] != nullptr))
	{
		// Cut instantly to camera one.
		Controller->SetViewTarget(Cameras[CamIndex]);
		++CamIndex;
	}
	else
	{
		CamIndex = 0;
	}
}

template<typename T>
void ACameraDirector::FindAllMovableActors(UWorld* World, TArray<T*>& Out)
{
	for (TActorIterator<AActor> It(World, T::StaticClass()); It; ++It)
	{
		T* Actor = Cast<T>(*It);
		if (Actor->IsRootComponentMovable() && Actor && !Actor->IsPendingKill()) //
		{
			Out.Emplace(Actor);
			UE_LOG(LogTemp, Warning, TEXT("Added Camera"));
		}
	}
}

