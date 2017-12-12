// Fill out your copyright notice in the Description page of Project Settings.

#include "SixWheeler.h"
#include "Components/InputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/CollisionProfile.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EngineUtils.h"
#include "Regex.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASixWheeler::ASixWheeler()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	SixWheelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PhysicalMesh"));
	SixWheelMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	SixWheelMesh->BodyInstance.bSimulatePhysics = true;
	SixWheelMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	SixWheelMesh->BodyInstance.bUseCCD = true;
	SixWheelMesh->bBlendPhysics = true;
	SixWheelMesh->bGenerateOverlapEvents = true;
	SixWheelMesh->SetCanEverAffectNavigation(false);
	RootComponent = SixWheelMesh;

	// Create a CameraComponent	
	MastCam = CreateDefaultSubobject<UCameraComponent>(TEXT("MastCam"));
	MastCam->SetupAttachment(SixWheelMesh);
	MastCam->RelativeLocation = FVector(-53.000084, 110.999878, 241.000000); // Position the camera
	MastCam->RelativeRotation = FRotator(0, 80, 0);
}

void ASixWheeler::BeginPlay()
{
	Super::BeginPlay();
	Super::BeginPlay();
	SetBoneArrays();

	World = GetWorld();
}

void ASixWheeler::SetBoneArrays()
{
	// Set Bone Arrays for controller
	SixWheelMesh->GetBoneNames(AllBones);

	WheelBones = FindControlStructures(TEXT("Wheel"));

	//wheels shouldn't rotate very fast
	for (auto& Str : WheelBones)
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected the following wheel: %s"), *Str.ToString());
		SixWheelMesh->SetPhysicsMaxAngularVelocity(MaxSpeed, false, Str);
	}

	BogeyBones = FindControlStructures(TEXT("Bogey.+(_F|_R)$"));
}

TArray<FName> ASixWheeler::FindControlStructures(FName Name)
{
	const FRegexPattern myPattern(Name.ToString());
	return  AllBones.FilterByPredicate([Name, myPattern](const FName& Str) {
		return !Str.IsNone() && FRegexMatcher(myPattern, Str.ToString()).FindNext();
	});
}

void ASixWheeler::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASixWheeler::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASixWheeler::MoveRight);
	PlayerInputComponent->BindAxis("LeftTouchpadY", this, &ASixWheeler::MoveForward);
	PlayerInputComponent->BindAxis("LookUp", this, &ASixWheeler::ViewUp);
	PlayerInputComponent->BindAxis("Turn", this, &ASixWheeler::ViewRight);
	PlayerInputComponent->BindAxis("ZoomIn", this, &ASixWheeler::ZoomIn);
	PlayerInputComponent->BindKey(EKeys::B, EInputEvent::IE_Pressed, this, &ASixWheeler::ToggleDrawControls);
}

void ASixWheeler::ViewRight(float Val)
{
	if (Val != 0)
	{
		Val = Val * GetWorld()->GetDeltaSeconds() * 45;
		MastCam->RelativeRotation.Yaw += Val;
	}
}

void ASixWheeler::ViewUp(float Val)
{
	if (Val != 0)
	{
		Val = Val * GetWorld()->GetDeltaSeconds() * -45;
		MastCam->RelativeRotation.Pitch += Val;
	}
}

void ASixWheeler::ZoomIn(float Val)
{
	MastCam->SetFieldOfView(MastCam->FieldOfView - Val);
}

void ASixWheeler::MoveForward(float Val)
{
	if (Val != 0)
	{
		FRotator Twist = FRotator().ZeroRotator;
		FVector BogeyTwist = GetActorUpVector();

		int i = 0;
		float powBogey = 0;
		for (auto& Bone : WheelBones)
		{
			Twist = SixWheelMesh->GetBoneQuaternion(Bone, EBoneSpaces::WorldSpace).Rotator();
			Twist.Roll = 0;
			FVector Torque = -Val * Twist.Vector() * WheelMotorTorque;

			SixWheelMesh->AddTorque(Torque, Bone, true);

			DrawVectors(Bone, Torque);

			FRotator Twist = SixWheelMesh->GetBoneQuaternion(Bone, EBoneSpaces::ComponentSpace).Rotator();
			auto PropControl = BogeyTwist * -Twist.Yaw * 500;

			// proportional control to straighten bogeys
			SixWheelMesh->SetPhysicsAngularVelocity(PropControl, false, Bone);
		}
	}
}

void ASixWheeler::MoveRight(float Val)
{
	FVector BogeyTwist = GetActorUpVector() * Val * BogeyMotorTorque;
	FRotator Twist = FRotator().ZeroRotator;

	int i = 0;
	float powWheel;
	float powBogey = 1;

	for (auto& Bone : WheelBones)
	{
		if (SixWheelMesh->GetPhysicsLinearVelocity().Size() < 30)
		{

			Twist = SixWheelMesh->GetBoneQuaternion(Bone, EBoneSpaces::WorldSpace).Rotator();
			Twist.Roll = 0;

			powWheel = FMath::Pow(-1, (i / 3));
			FVector Torque = Val * Twist.Vector() * WheelMotorTorque * powWheel; //-Val *


			SixWheelMesh->AddTorque(Torque, Bone, true);

			DrawVectors(Bone, Torque);

			if (i < 4)
			{
				if ((i == 0) || (i == 3)) { powBogey = 1; }
				else { powBogey = -1; }

				FRotator Twist = SixWheelMesh->GetBoneQuaternion(BogeyBones[i], EBoneSpaces::ComponentSpace).Rotator();
				auto PropControl = BogeyTwist.GetAbs() * -(Twist.Yaw + powBogey * 45) * 0.1;

				SixWheelMesh->SetPhysicsAngularVelocity(PropControl, false, BogeyBones[i]);
			}
		}

		else if (i < 4)
		{
			float powBogey2 = FMath::Pow(-1, ((i + 1) % 2));
			SixWheelMesh->SetPhysicsAngularVelocity(powBogey2*BogeyTwist, false, BogeyBones[i]);
		}
		++i;
	}
}

void ASixWheeler::ToggleDrawControls()
{
	bDraw = !bDraw;
}

void ASixWheeler::DrawVectors(FName Bone, FVector Torque)
{
	if (bDraw)
	{
		Torque = Torque.RotateAngleAxis(90, GetActorUpVector()) / 5000;
		FVector ArrowStart = SixWheelMesh->GetBoneLocation(Bone, EBoneSpaces::WorldSpace);
		DrawDebugDirectionalArrow(World, ArrowStart, ArrowStart - Torque,
			20, FColor::Green, false, World->GetDeltaSeconds() * 1.1, (uint8)'\000', 2.f);
	}

}