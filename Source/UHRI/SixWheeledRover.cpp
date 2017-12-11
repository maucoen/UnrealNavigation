// Fill out your copyright notice in the Description page of Project Settings.

#include "SixWheeledRover.h"
#include "Components/InputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/CollisionProfile.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EngineUtils.h"
#include "UHRIHUD.h"
#include "Regex.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
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

	// Create a CameraComponent	
	MastCam = CreateDefaultSubobject<UCameraComponent>(TEXT("MastCam"));
	MastCam->SetupAttachment(SixWheelMesh);
	MastCam->RelativeLocation = FVector(-53.000084, 110.999878, 241.000000); // Position the camera
	MastCam->RelativeRotation = FRotator(0, 80, 0);

	// Create a Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(SixWheelMesh);
	//SpringArm->SetupAttachment(SixWheelMesh);
	//SpringArm->RelativeLocation = FVector(-53.000084, 110.999878, 241.000000); // Position the camera
	//SpringArm->RelativeRotation = FRotator(0, 80, 0);

	//// Create a Cine Cam
	//CineCam = CreateDefaultSubobject<UCineCameraComponent>(TEXT("CineCam"));
	//..CineCam->SetupAttachment(SpringArm);
	//CineCam->RelativeLocation = FVector(-53.000084, 110.999878, 241.000000); // Position the camera
	//CineCam->RelativeRotation = FRotator(0, 80, 0);

}

// Called when the game starts or when spawned
void ASixWheeledRover::BeginPlay()
{
	Super::BeginPlay();
	SetBoneArrays();

	World = GetWorld();

	// use our custom HUD class
	//HUDClass = AUHRIHUD::StaticClass();

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
		SixWheelMesh->SetPhysicsMaxAngularVelocity(MaxSpeed, false, Str);
	}

	BogeyBones = FindControlStructures(TEXT("Bogey.+(_F|_R)$"));
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
	PlayerInputComponent->BindAxis("LeftTouchpadY", this, &ASixWheeledRover::MoveForward);
	PlayerInputComponent->BindAxis("LookUp", this, &ASixWheeledRover::ViewUp);
	PlayerInputComponent->BindAxis("Turn", this, &ASixWheeledRover::ViewRight);
	PlayerInputComponent->BindAxis("ZoomIn", this, &ASixWheeledRover::ZoomIn);
	PlayerInputComponent->BindKey(EKeys::B, EInputEvent::IE_Pressed, this, &ASixWheeledRover::ToggleDrawControls);
}

void ASixWheeledRover::OnToggleCamera()
{
	//ChangeCam(!bMastCamActive, true);
}

void ASixWheeledRover::ChangeCam(const bool bState, const bool bForce)
{
	/*if ((bState != bMastCamActive) || (bForce == true))
	{
		bMastCamActive = bState;

		if (bState == true)
		{
			MastCam->Deactivate();
			CineCam->Activate();
		}
		else
		{
			CineCam->Deactivate();
			MastCam->Activate();
		}*/


		//TODO: HUD stuff
		/*InCarSpeed->SetVisibility(bInCarCameraActive);
		InCarGear->SetVisibility(bInCarCameraActive);*/
	//}
}

void ASixWheeledRover::ViewRight(float Val)
{
	if (Val != 0)
	{ 
		Val = Val * GetWorld()->GetDeltaSeconds() * 45;
		MastCam->RelativeRotation.Yaw += Val;
	}
}

void ASixWheeledRover::ViewUp(float Val)
{
	if (Val != 0)
	{
		Val = Val * GetWorld()->GetDeltaSeconds() * -45;
		MastCam->RelativeRotation.Pitch += Val;
	}
}

void ASixWheeledRover::ZoomIn(float Val)
{
	MastCam->SetFieldOfView(MastCam->FieldOfView - Val);
}

void ASixWheeledRover::MoveForward(float Val)
{
	if (Val != 0)
	{
		FRotator Twist = FRotator().ZeroRotator;
		FVector BogeyTwist =  GetActorUpVector();

		int i = 0;
		float powBogey =0;
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

void ASixWheeledRover::MoveRight(float Val)
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
			FVector Torque =  Val * Twist.Vector() * WheelMotorTorque * powWheel; //-Val *

			
			SixWheelMesh->AddTorque(Torque, Bone, true);

			DrawVectors(Bone, Torque);

			if (i < 4)
			{
				if ((i == 0) || (i == 3)) { powBogey = 1; }
				else { powBogey = -1; }
				
				FRotator Twist = SixWheelMesh->GetBoneQuaternion(BogeyBones[i], EBoneSpaces::ComponentSpace).Rotator();
				auto PropControl = BogeyTwist.GetAbs() * -(Twist.Yaw + powBogey*45) * 0.1;

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

void ASixWheeledRover::ToggleDrawControls()
{
	bDraw = !bDraw;
}

void ASixWheeledRover::DrawVectors(FName Bone, FVector Torque)
{
	if (bDraw)
	{

		Torque = Torque.RotateAngleAxis(90, GetActorUpVector()) / 5000;
		FVector ArrowStart = SixWheelMesh->GetBoneLocation(Bone, EBoneSpaces::WorldSpace);
		DrawDebugDirectionalArrow(World, ArrowStart, ArrowStart - Torque,
			20, FColor::Green, false, World->GetDeltaSeconds() * 1.1, (uint8)'\000', 2.f);
	}
	
}

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