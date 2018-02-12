// Copyright 2017, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once
#include "CoreMinimal.h"
#include "EngineUtils.h"

/**
* Coordinate conversion helper functions
*/
struct FCoordConvStatics
{
	/** 
	 * Convert 
	 * Unreal's 'Z up', 'X forward', 'Y right' 'left handed' coordinate system
	 * to 
	 * ROS's 'Z up', 'X forward', 'Y left' 'right handed' coordinate system
	 *
	 * http://www.ros.org/reps/rep-0103.html
	 */
	
	// FTransform by value
	static FORCEINLINE FTransform UToROS(const FTransform& InTransform)
	{
		return FTransform(UToROS(InTransform.GetRotation()), UToROS(InTransform.GetLocation()));
	}
	
	// FQuat by value
	static FORCEINLINE FQuat UToROS(const FQuat& InQuat)
	{
		// todo
		//return FQuat(- InQuat.X, InQuat.Y, InQuat.Z, - InQuat.W);
		return InQuat;
	}
	
	// FVector by value
	static FORCEINLINE FVector UToROS(const FVector& InVector)
	{
		return FVector(InVector.X * 0.01f, - InVector.Y * 0.01f, InVector.Z * 0.01f);
	}
	
	// FTransform by reference
	static FORCEINLINE void UToROS(FTransform& OutTransform)
	{
		OutTransform.SetRotation(UToROS(OutTransform.GetRotation()));
		OutTransform.SetLocation(UToROS(OutTransform.GetLocation()));		
	}
	
	// FQuat by reference
	static FORCEINLINE void UToROS(FQuat& OutQuat)
	{
		OutQuat.X *= -1;
		OutQuat.W *= -1;
	}

	// FVector by reference
	static FORCEINLINE void UToROS(FVector& OutVector)
	{
		OutVector.Y *= -1;
	}
	
	/**
	* Convert
	* ROS's 'Z up', 'X forward', 'Y left' 'right handed' coordinate system
	* to
	* Unreal's 'Z up', 'X forward', 'Y right' 'left handed' coordinate system
	*
	* http://www.ros.org/reps/rep-0103.html
	*/

	// FTransform by value
	static FORCEINLINE FTransform ROSToU(const FTransform& InTransform)
	{
		return FTransform(ROSToU(InTransform.GetRotation()), ROSToU(InTransform.GetLocation()));
	}

	// FQuat by value
	static FORCEINLINE FQuat ROSToU(const FQuat& InQuat)
	{
		return FQuat(-InQuat.X, InQuat.Y, InQuat.Z, -InQuat.W);
	}

	// FVector by value
	static FORCEINLINE FVector ROSToU(const FVector& InVector)
	{
		return FVector(InVector.X * 0.01f, -InVector.Y * 0.01f, InVector.Z * 0.01f);
	}

	// FTransform by reference
	static FORCEINLINE void ROSToU(FTransform& OutTransform)
	{
		OutTransform.SetRotation(ROSToU(OutTransform.GetRotation()));
		OutTransform.SetLocation(ROSToU(OutTransform.GetLocation()));
	}

	// FQuat by reference
	static FORCEINLINE void ROSToU(FQuat& OutQuat)
	{
		OutQuat.X *= -1;
		OutQuat.W *= -1;
	}

	// FVector by reference
	static FORCEINLINE void ROSToU(FVector& OutVector)
	{
		OutVector.Y *= -1;
	}


	/** 
	 * Convert 
	 * Unreal's 'Z up', 'X forward', 'Y right' 'left handed' coordinate system 
	 * to 
	 * ROS's Camera 'Z forward', 'X right', 'Y down' 'right handed' coordinate system
	 *
	 * http://www.ros.org/reps/rep-0103.html
	 */
	
	 // FTransform by value
	static FORCEINLINE FTransform UToROSCamera(const FTransform& InTransform)
	{
		// todo
		return FTransform(UToROSCamera(InTransform.GetRotation()), UToROSCamera(InTransform.GetLocation()));
	}

	// FQuat by value
	static FORCEINLINE FQuat UToROSCamera(const FQuat& InQuat)
	{
		// todo
		return FQuat(-InQuat.X, InQuat.Y, InQuat.Z, -InQuat.W);
	}

	// FVector by value
	static FORCEINLINE FVector UToROSCamera(const FVector& InVector)
	{
		// todo
		return FVector(InVector.X * 0.01f, -InVector.Y * 0.01f, InVector.Z * 0.01f);
	}

	// FTransform by reference
	static FORCEINLINE void UToROSCamera(FTransform& OutTransform)
	{
		// todo
		OutTransform.SetRotation(UToROSCamera(OutTransform.GetRotation()));
		OutTransform.SetLocation(UToROSCamera(OutTransform.GetLocation()));
	}

	// FQuat by reference
	static FORCEINLINE void UToROSCamera(FQuat& OutQuat)
	{
		// todo
		OutQuat.X *= -1;
		OutQuat.W *= -1;
	}

	// FVector by reference
	static FORCEINLINE void UToROSCamera(FVector& OutVector)
	{
		// todo
		OutVector.Y *= -1;
	}

	/**
	* Convert
	* ROS's Camera 'Z forward', 'X right', 'Y down' 'right handed' coordinate system
	* to
	* Unreal's 'Z up', 'X forward', 'Y right' 'left handed' coordinate system
	*
	* http://www.ros.org/reps/rep-0103.html
	*/

	// FTransform by value
	static FORCEINLINE FTransform ROSCameraToU(const FTransform& InTransform)
	{
		// todo
		return FTransform(ROSCameraToU(InTransform.GetRotation()), ROSCameraToU(InTransform.GetLocation()));
	}

	// FQuat by value
	static FORCEINLINE FQuat ROSCameraToU(const FQuat& InQuat)
	{
		// todo
		return FQuat(-InQuat.X, InQuat.Y, InQuat.Z, -InQuat.W);
	}

	// FVector by value
	static FORCEINLINE FVector ROSCameraToU(const FVector& InVector)
	{
		// todo
		return FVector(InVector.X * 0.01f, -InVector.Y * 0.01f, InVector.Z * 0.01f);
	}

	// FTransform by reference
	static FORCEINLINE void ROSCameraToU(FTransform& OutTransform)
	{
		// todo
		OutTransform.SetRotation(ROSCameraToU(OutTransform.GetRotation()));
		OutTransform.SetLocation(ROSCameraToU(OutTransform.GetLocation()));
	}

	// FQuat by reference
	static FORCEINLINE void ROSCameraToU(FQuat& OutQuat)
	{
		// todo
		OutQuat.X *= -1;
		OutQuat.W *= -1;
	}

	// FVector by reference
	static FORCEINLINE void ROSCameraToU(FVector& OutVector)
	{
		// todo
		OutVector.Y *= -1;
	}
};