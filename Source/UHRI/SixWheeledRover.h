// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "SixWheeledRover.generated.h"

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
	
public:
	

protected:
	// APawn interface
	void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
	
	// Called when the game starts or when spawned
	void BeginPlay() override;

	//void Tick(float DeltaTime) override;

	void SetBoneArrays();

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
		FVector MariasLocation;

	UPROPERTY(EditAnywhere)
		float Speed;

	UPROPERTY(EditAnywhere)
		float BogeyMotorTorque = 80;

	UPROPERTY(EditAnywhere)
		float WheelMotorTorque = 100000000;

private:
	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;
	
	TArray<FName> FindControlStructures(FName Name);
	TArray<FName> AllBones;
	TArray<FName> WheelBones;
	TArray<FName> FrontBogeyBones;
	TArray<FName> BackBogeyBones;
	
	void MoveForward(float Val);
	void MoveRight(float Val);
};
