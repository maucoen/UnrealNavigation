// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UHRI : ModuleRules
{
	public UHRI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
            "Slate", "HeadMountedDisplay", "UMG", "SlateCore", "OnlineSubsystem", "GameLiftServerSDK","GameLiftClientSDK", "PhysXVehicles" }); //
        PublicAdditionalLibraries.Add("C:\\Program Files\\MATLAB\\R2017A\\extern\\lib\\win64\\microsoft\\libmat.lib");
        PublicAdditionalLibraries.Add("C:\\Program Files\\MATLAB\\R2017A\\extern\\lib\\win64\\microsoft\\libmx.lib");
        PublicAdditionalLibraries.Add("C:\\Program Files\\MATLAB\\R2017A\\extern\\lib\\win64\\microsoft\\libeng.lib");
    }
}
