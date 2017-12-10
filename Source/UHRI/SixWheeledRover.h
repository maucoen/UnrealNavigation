// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "Camera/CameraComponent.h"
#include "SixWheeledRover.generated.h"

class USpringArmComponent;
//
/**
 * 
 */
UCLASS()
class UHRI_API ASixWheeledRover : public AWheeledVehicle
{
	GENERATED_BODY()
	
		ASixWheeledRover(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* SixWheelMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* MastCam;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	//	class UCineCameraComponent* CineCam;
	
public:
	

protected:
	// APawn interface
	void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	void OnToggleCamera();
	void ChangeCam(const bool bState, const bool bForce);
	void ViewRight(float Val);
	void ViewUp(float Val);
	void ZoomIn(float Val);
	// End of APawn interface
	
	// Called when the game starts or when spawned
	void BeginPlay() override;

	//void Tick(float DeltaTime) override;

	void SetBoneArrays();

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
		FVector MariasLocation;

	UPROPERTY(EditAnywhere)
		float Speed = 150;

	UPROPERTY(EditAnywhere)
		float BogeyMotorTorque = 80;

	UPROPERTY(EditAnywhere)
		float WheelMotorTorque = 100000000;

private:


	bool bMastCamActive;

	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;
	
	TArray<FName> FindControlStructures(FName Name);
	TArray<FName> AllBones;
	TArray<FName> WheelBones;
	TArray<FName> FrontBogeyBones;
	TArray<FName> BackBogeyBones;
	
	UFUNCTION()
	void MoveForward(float Val);

	UFUNCTION()
	void MoveRight(float Val);

	void ToggleDrawControls();

	void DrawVectors(FName Bone, FVector Torque);

	bool bDraw = true;
};
