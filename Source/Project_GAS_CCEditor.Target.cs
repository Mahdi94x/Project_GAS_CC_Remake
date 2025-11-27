// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Project_GAS_CCEditorTarget : TargetRules
{
    public Project_GAS_CCEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V6;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;

        BuildEnvironment = TargetBuildEnvironment.Shared;

        bOverrideBuildEnvironment = true;

        ExtraModuleNames.Add("Project_GAS_CC");
    }
}

