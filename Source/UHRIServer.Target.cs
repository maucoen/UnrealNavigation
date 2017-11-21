// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class UHRIServerTarget : TargetRules    // Change this line of code as shown previously
{
    public UHRIServerTarget(TargetInfo Target) : base(Target) // Change this line of code as shown previously
    {
        Type = TargetType.Server;
        ExtraModuleNames.Add("UHRI");   // Change this line of code as shown previously
    }
}