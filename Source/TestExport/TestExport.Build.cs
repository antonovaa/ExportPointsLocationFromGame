// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestExport : ModuleRules
{
	public TestExport(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Json", "JsonUtilities", "Http", "GameplayTags" });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
