using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Desktop)]
public class CleanThirdPersonClientTarget : TargetRules
{ 
	public CleanThirdPersonClientTarget(TargetInfo Target) : base(Target)
    {
		bUsesSteam = false;
		bUseLoggingInShipping = true;
		Type = TargetType.Client;
        ExtraModuleNames.Add("CleanThirdPerson");        
    }
}