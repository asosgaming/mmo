// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CleanThirdPersonTarget : TargetRules
{
	public CleanThirdPersonTarget(TargetInfo Target) : base(Target)
    {
		bUseLoggingInShipping = true;
		Type = TargetType.Game;
        ExtraModuleNames.Add("CleanThirdPerson");		
	}
}
