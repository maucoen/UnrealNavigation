// Fill out your copyright notice in the Description page of Project Settings.

#include "Rover.h"
#include "Camera/CameraComponent.h"
#include "Components/MeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ARover

ARover::ARover()
{
	// Set size for collision capsule
	//GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	RoverCamComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("RoverCam"));
	RoverCamComponent->SetupAttachment(RootComponent);
	RoverCamComponent->RelativeLocation = FVector(45.f, 0.f, 145.f); // Position the camera
	RoverCamComponent->bUsePawnControlRotation = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(RoverCamComponent);
	BoxComponent->RelativeLocation = FVector(-117.f, -46.f, -124.f); // Position the camera
																	 //BoxComponent->SetRelativeScale3D(FVector::Set(5.f, 4.5f, 3.25f));

																	 // Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	RoverMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RoverMesh"));
	RoverMesh->SetupAttachment(RoverCamComponent);
	RoverMesh->bCastDynamicShadow = true;
	RoverMesh->CastShadow = true;
	RoverMesh->RelativeRotation = FRotator(0.f, 0.f, 270.f);
	RoverMesh->RelativeLocation = FVector(-127.5f, -54.4f, -237.f);


}

void ARover::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARover::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARover::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARover::MoveRight);


	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void ARover::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ARover::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ARover::Tick(float DeltaTime)
{
	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTravelled = (Location - GlobalStartLocation).Size();

		if (JourneyTravelled >= JourneyLength)
		{
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
		}

		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += Speed * DeltaTime * Direction;
		SetActorLocation(Location);
	}

}
