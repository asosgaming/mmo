// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CleanThirdPerson : ModuleRules
{
	public CleanThirdPerson(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		bEnforceIWYU = true;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore", "Sockets", "Networking", "MoviePlayer" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		 PrivateDependencyModuleNames.Add("OnlineSubsystem");
         PrivateDependencyModuleNames.Add("OnlineSubsystemNull");

		
	}
}
