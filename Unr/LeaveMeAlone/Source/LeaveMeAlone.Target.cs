// LeaveMeAlone Game by Netologiya. All RightsReserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LeaveMeAloneTarget : TargetRules
{
	public LeaveMeAloneTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "LeaveMeAlone" } );
	}
}
