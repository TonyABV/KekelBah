// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KekelBah : ModuleRules
{
	public KekelBah(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine", 
            "InputCore", 
            "Niagara",
			"PhysicsCore"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[] 
        {
            "KekelBah/Public/Player",
			"KekelBah/Public/Player/Components",
			"KekelBah/Public/Dev",
			"KekelBah/Public/Weapon"
		});
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
