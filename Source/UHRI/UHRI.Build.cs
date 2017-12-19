// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UHRI : ModuleRules
{
	public UHRI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
            "Slate", "HeadMountedDisplay", "UMG", "SlateCore", "OnlineSubsystem", "GameLiftServerSDK","GameLiftClientSDK", "PhysXVehicles" }); //
    }
}
