// Cesar Molto Morilla

using UnrealBuildTool;
using System.Collections.Generic;

public class Recruitment_ProjectTarget : TargetRules
{
	public Recruitment_ProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Recruitment_Project" } );
	}
}
