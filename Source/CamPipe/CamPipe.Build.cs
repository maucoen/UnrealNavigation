// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CamPipe : ModuleRules
{
	public CamPipe(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
            "UROSBridge",
			"UCoordConv",
			"UnrealCV",
            "Json",
            "JsonUtilities","PhysXVehicles", "HeadMountedDisplay" });

		Definitions.Add("HMD_MODULE_INCLUDED=1");
	}
}
