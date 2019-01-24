// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
 
using UnrealBuildTool;
using System.Collections.Generic;
 
 [SupportedPlatforms(UnrealPlatformClass.Server)]
public class CleanThirdPersonServerTarget : TargetRules
{
    public CleanThirdPersonServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
		bUsesSteam = false;
		bUseLoggingInShipping = true;
        ExtraModuleNames.Add("CleanThirdPerson");
    }
}