// Fill out your copyright notice in the Description page of Project Settings.

#include "SixWheeledRover.h"
#include "Components/InputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/CollisionProfile.h"
#include "Components/SkeletalMeshComponent.h"
#include "EngineUtils.h"
#include "Regex.h"
#include "SimpleWheeledVehicleMovementComponent.h"

FName SixWheelMoveComp = AWheeledVehicle::VehicleMovementComponentName;

ASixWheeledRover::ASixWheeledRover(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USimpleWheeledVehicleMovementComponent>(SixWheelMoveComp))
{
	//PrimaryActorTick.bCanEverTick = true;

	//SetMobility(EComponentMobility::Movable);

	SixWheelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PhysicalMesh"));
	SixWheelMesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	SixWheelMesh->BodyInstance.bSimulatePhysics = true;
	SixWheelMesh->BodyInstance.bNotifyRigidBodyCollision = true;
	SixWheelMesh->BodyInstance.bUseCCD = true;
	SixWheelMesh->bBlendPhysics = true;
	SixWheelMesh->bGenerateOverlapEvents = true;
	SixWheelMesh->SetCanEverAffectNavigation(false);
	RootComponent = SixWheelMesh;
}

// Called when the game starts or when spawned
void ASixWheeledRover::BeginPlay()
{
	Super::BeginPlay();
	SetBoneArrays();

	/*GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(MariasLocation);*/
}

void ASixWheeledRover::SetBoneArrays()
{
	// Set Bone Arrays for controller
	SixWheelMesh->GetBoneNames(AllBones);

	WheelBones = FindControlStructures(TEXT("Wheel"));

	//wheels shouldn't rotate very fast
	for (auto& Str : WheelBones)
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected the following wheel: %s"), *Str.ToString());
		SixWheelMesh->SetPhysicsMaxAngularVelocity(300, false, Str);
	}

	FrontBogeyBones = FindControlStructures(TEXT("Bogey.+(_F|_R)$"));
}

TArray<FName> ASixWheeledRover::FindControlStructures(FName Name)
{
	const FRegexPattern myPattern(Name.ToString());
	return  AllBones.FilterByPredicate([Name, myPattern](const FName& Str) {
		return !Str.IsNone() && FRegexMatcher(myPattern, Str.ToString()).FindNext();
	});	
}

void ASixWheeledRover::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASixWheeledRover::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASixWheeledRover::MoveRight);
	PlayerInputComponent->BindAxis("LookUp");
	PlayerInputComponent->BindAxis("LookRight");
}

void ASixWheeledRover::MoveForward(float Val)
{
	if (Val != 0)
	{
		FVector Torque = -GetActorForwardVector() * Val * WheelMotorTorque;

		for (auto& Bone : WheelBones)
		{
			SixWheelMesh->AddTorque(Torque, Bone, false);
		}
	}
	FQuat Loc = SixWheelMesh->GetBoneQuaternion("Bogey_L_F", EBoneSpaces::ComponentSpace);
}

void ASixWheeledRover::MoveRight(float Val)
{
	FVector Torque = GetActorUpVector() * Val * BogeyMotorTorque;
	FVector TorqueF = -GetActorForwardVector() * Val * WheelMotorTorque;

	if (SixWheelMesh->GetPhysicsLinearVelocity().Size() < 50) //stationary, rotate in place
	{
		int i = 0;
		float powWheel;
		float powBogey;
		for (auto& Bone : WheelBones)
		{
			powWheel = FMath::Pow(-1, (i / 3));
			SixWheelMesh->AddTorque(TorqueF*powWheel, Bone, true);

			if (i < 4) 
			{ 
				if ((i == 0) || (i == 3)) { powBogey = -1; }
				else { powBogey = 1; }

				SixWheelMesh->SetPhysicsAngularVelocity(powBogey*Torque.GetAbs(), false, FrontBogeyBones[i]); 
			}
	
			++i;
		}
	}
	else // forward moving speed, rotate bogeys according to turn direction
	{
		int i = 0;
		for (auto& Bone : FrontBogeyBones)
		{
			float powBogey = FMath::Pow(-1, ((i+1) % 2));
			if (Val != 0)
			{
				SixWheelMesh->SetPhysicsAngularVelocity(powBogey*Torque, false, FrontBogeyBones[i]);
				++i;
			}
		}
	}
}	


//void ASixWheeledRover::OnHandbrakePressed()
//{
//	GetVehicleMovementComponent()->SetHandbrakeInput(true);
//}
//
//void ASixWheeledRover::OnHandbrakeReleased()
//{
//	GetVehicleMovementComponent()->SetHandbrakeInput(false);
//}

//void ASixWheeledRover::OnToggleCamera()
//{
//	EnableIncarView(!bInCarCameraActive);
//}

//void ASixWheeledRover::EnableIncarView(const bool bState, const bool bForce)
//{
//	if ((bState != bInCarCameraActive) || (bForce == true))
//	{
//		bInCarCameraActive = bState;
//
//		if (bState == true)
//		{
//			OnResetVR();
//			Camera->Deactivate();
//			InternalCamera->Activate();
//		}
//		else
//		{
//			InternalCamera->Deactivate();
//			Camera->Activate();
//		}
//
//		InCarSpeed->SetVisibility(bInCarCameraActive);
//		InCarGear->SetVisibility(bInCarCameraActive);
//	}
//}

//void ASixWheeledRover::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//
//	UE_LOG(LogTemp, Warning, TEXT("We came into tick function"));
//
//
//	FVector Location = GetActorLocation();
//	float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
//	float JourneyTravelled = (Location - GlobalStartLocation).Size();
//
//	if (JourneyTravelled >= JourneyLength)
//	{
//
//		//Speed = 0;
//		FVector Swap = GlobalStartLocation;
//		GlobalStartLocation = GlobalTargetLocation;
//		GlobalTargetLocation = Swap;
//	}
//
//	FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
//	Location += (Speed * DeltaTime)* Direction;
//	SetActorLocation(Location, false, nullptr, ETeleportType::TeleportPhysics);
//}