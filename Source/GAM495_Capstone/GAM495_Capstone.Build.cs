// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAM495_Capstone : ModuleRules
{
	public GAM495_Capstone(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"Niagara",  // for implementing particles
			"UMG",  // for using UMG, or implementing user widgets and UI elements
			"NavigationSystem"  // for controlling AI movement
        });
	}
}
