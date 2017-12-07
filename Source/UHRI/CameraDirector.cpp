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
		InputComponent->bBlockInput = bBlockInput;

		if (InputComponent)
		{
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
				UE_LOG(LogTemp, Warning, TEXT("Camera Iterator: Added %s"), *Actor->GetName());
			}
		}
	}
	//Remove last element from array, which seems to be a generic camera actor
	UE_LOG(LogTemp, Warning, TEXT("Camera Iterator: popped %s"), *Out.Pop()->GetName());



	//	//////////
	//	void* GameLiftServerSDKLibraryHandle = nullptr;
	//	
	//	FString BaseDir = IPluginManager::Get().FindPlugin("GameLiftServerSDK")->GetBaseDir();
	//	UE_LOG(LogTemp, Warning, TEXT("BaseDir %s"), *BaseDir);
	//	
	//	const FString SDKDir = FPaths::Combine(*BaseDir, TEXT("ThirdParty"), TEXT("GameLiftServerSDK"));
	//	UE_LOG(LogTemp, Warning, TEXT("SDKDir %s"), *SDKDir);
	//
	//	const FString LibName = TEXT("aws-cpp-sdk-gamelift-server");
	//	
	//	const FString LibDir = FPaths::Combine(*SDKDir, TEXT("Win64"));
	//	UE_LOG(LogTemp, Warning, TEXT("LibeDir %s"), *LibDir);
	//	
	//	//if (!LoadDependency(LibDir, LibName, GameLiftServerSDKLibraryHandle))
	//	//{
	//	//	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT(LOCTEXT_NAMESPACE, "Failed to load aws-cpp-sdk-gamelift-server library. Plug-in will not be functional."));
	//	//}
	//
	//	FString Lib = LibName + TEXT(".") + FPlatformProcess::GetModuleExtension();
	//	UE_LOG(LogTemp, Warning, TEXT("Lib %s"), *Lib);
	//
	//	FString Path = LibDir.IsEmpty() ? *Lib : FPaths::Combine(*LibDir, *Lib);
	//	UE_LOG(LogTemp, Warning, TEXT("Path %s"), *Path);
	//
	//	GameLiftServerSDKLibraryHandle = FPlatformProcess::GetDllHandle(*Path);
	//	//UE_LOG(LogTemp, Warning, TEXT("jandle %s"), GameLiftServerSDKLibraryHandle);
}

