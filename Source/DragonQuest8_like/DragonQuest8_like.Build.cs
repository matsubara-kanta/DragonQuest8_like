// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DragonQuest8_like : ModuleRules
{
    public DragonQuest8_like(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "SlateCore", "Slate","UMG", "MoviePlayer"});
        PublicDependencyModuleNames.AddRange(new string[] { "DragonQuest8_like" });
    }
}
