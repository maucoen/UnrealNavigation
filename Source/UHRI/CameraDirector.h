// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "CameraDirector.generated.h"

UCLASS()
class UHRI_API ACameraDirector : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		TArray<AActor*> Cameras;

	template<typename T>
	void FindAllMovableCameraComponents(UWorld* World, TArray<T*>& Out);

public:
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetCameraSwitchInput();

	int32 CamIndex = 1;
	APlayerController* Controller;

	UFUNCTION()
	void SwitchCam();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};

