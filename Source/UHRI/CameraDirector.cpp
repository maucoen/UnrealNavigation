// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"
#include "Core.h"
#include "Engine.h"
#include "ModuleManager.h"
#include "IPluginManager.h"

#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

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
			InputComponent->BindKey(EKeys::M, EInputEvent::IE_Pressed, this, &ACameraDirector::SwitchCam);
			EnableInput(Controller);
			InputComponent->BindKey(EKeys::MotionController_Left_Grip1, EInputEvent::IE_Pressed, this, &ACameraDirector::SwitchCam);
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

	auto cam = Cameras[CamIndex]->GetName();
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Cameras[CamIndex]->GetName(), true, FVector2D(2,2)); }
}

template<typename T>
void ACameraDirector::FindAllMovableCameraComponents(UWorld* World, TArray<T*>& Out)
{
	for (TActorIterator<AActor> It(World, T::StaticClass()); It; ++It)
	{
		T* Actor = Cast<T>(*It);
		if (Actor->IsRootComponentMovable() && Actor && !Actor->IsPendingKill() && Actor->FindComponentByClass<UCameraComponent>())
		{
				Out.Emplace(Actor);
				UE_LOG(LogTemp, Warning, TEXT("Camera Iterator added: %s"), *Actor->GetName());
		}
	}
	//Remove last element from array, which seems to be a generic camera actor
	FString Popped = Out.Pop()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Camera Iterator: popped %s"), *Popped);
}

