// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "SixWheeler.generated.h"

class USpringArmComponent;

UCLASS()
class UNREALNAVIGATION_API ASixWheeler : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASixWheeler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* SixWheelMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* MastCam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;



protected:

	//void OnToggleCamera();
	//void ChangeCam(const bool bState, const bool bForce);
	//void ViewRight(float Val);
	//void ViewUp(float Val);
	//void ZoomIn(float Val);

	void SetBoneArrays();

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
		FVector MariasLocation;

	UPROPERTY(EditAnywhere)
		float MaxSpeed = 150;

	UPROPERTY(EditAnywhere)
		float BogeyMotorTorque = 80;

	UPROPERTY(EditAnywhere)
		float WheelMotorTorque = 100000000;

private:

	bool bMastCamActive;

	UWorld* World;

	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

	TArray<FName> FindControlStructures(FName Name);
	TArray<FName> AllBones;
	TArray<FName> WheelBones;
	TArray<FName> BogeyBones;

	UFUNCTION()
		void MoveForward(float Val);

	UFUNCTION()
		void MoveRight(float Val);

	void ToggleDrawControls();

	void DrawVectors(FName Bone, FVector Torque);

	bool bDraw = true;
};
