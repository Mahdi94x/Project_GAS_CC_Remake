// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_GAS_CC : ModuleRules
{
	public Project_GAS_CC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });


	}
}
