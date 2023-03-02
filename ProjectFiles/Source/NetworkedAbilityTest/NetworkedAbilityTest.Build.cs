// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NetworkedAbilityTest : ModuleRules
{
	public NetworkedAbilityTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "NavigationSystem", "AIModule" });
	}
}
