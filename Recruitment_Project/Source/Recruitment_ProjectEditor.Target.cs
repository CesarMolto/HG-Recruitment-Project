// Cesar Molto Morilla

using UnrealBuildTool;
using System.Collections.Generic;

public class Recruitment_ProjectEditorTarget : TargetRules
{
	public Recruitment_ProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Recruitment_Project" } );
	}
}
