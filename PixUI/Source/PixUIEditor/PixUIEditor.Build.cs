// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PixUIEditor : ModuleRules
{
	public PixUIEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
                "PixUI/Public",
                "PixUI/Private",
                "PixUIEditor/Public",
                "PixUIEditor/Private"
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[] {
                "ContentBrowser",
				"Core",
				"CoreUObject",
                "DesktopPlatform",
                "DesktopWidgets",
				"EditorStyle",
				"Engine",
				"InputCore",
				"Projects",
				"Slate",
				"SlateCore",
				"PixUI",
				"UnrealEd",
				"UMG"
			});
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		//////////////////////////////////////////////
		///be unity cpp file for build
#if UE_4_21_OR_LATER
        bool bUseUnity = true;
		System.Console.WriteLine("PixUIEditor bUseUnity           ----- : " + bUseUnity);
#endif  //UE_4_21_OR_LATER
		////////////////////////////////////////////// 
	}
}
