// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class TDM : ModuleRules
{
	public TDM(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

#if UE_4_20_OR_LATER
		// ue 4.20 or later do not need PublicIncludePaths
#else
		PublicIncludePaths.AddRange(
			new string[] {
				"TDM/Public"
				// ... add public include paths required here ...
			}
			);
#endif
				
		PrivateIncludePaths.AddRange(
			new string[] {
				"TDM/Private",
				// ... add other private include paths required here ...
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
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            //Add Android
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            string aplPath = Path.Combine(PluginPath, "TDM_APL.xml");
#if UE_4_20_OR_LATER
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", aplPath);
#else
            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", aplPath));
#endif
            System.Console.WriteLine("TDM APL Path = " + aplPath);
#if UE_4_24_OR_LATER
            PublicSystemLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/TDM/libs/armeabi-v7a")));
            PublicSystemLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/TDM/libs/arm64-v8a")));
            PublicSystemLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/TDM/libs/x86")));
            PublicSystemLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/TDM/libs/x86_64")));
#else
			PublicLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/TDM/libs/armeabi-v7a")));
            PublicLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/TDM/libs/arm64-v8a")));
            PublicLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/TDM/libs/x86")));
            PublicLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/TDM/libs/x86_64")));
#endif
			
			PublicAdditionalLibraries.Add("TDataMaster");

        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            System.Console.WriteLine("--------------Add iOS TDM");
            //IOSStart not delete
			#if UE_4_22_OR_LATER 
				PublicAdditionalFrameworks.Add(new Framework("TDataMaster", "lib/iOS/TDataMaster.embeddedframework.zip", "")); 
				PublicAdditionalFrameworks.Add(new Framework("TDMIDFA", "lib/iOS/TDMIDFA.embeddedframework.zip", ""));
				PublicAdditionalFrameworks.Add(new Framework("TDMASA", "lib/iOS/TDMASA.embeddedframework.zip", ""));
				PublicAdditionalFrameworks.Add(new Framework("tgpasimple", "lib/iOS/tgpasimple.embeddedframework.zip", ""));
				PublicAdditionalFrameworks.Add(new Framework("TDMQimeiSDK", "lib/iOS/TDMQimeiSDK.embeddedframework.zip", ""));
			#else 
				PublicAdditionalFrameworks.Add(new UEBuildFramework("TDataMaster", "lib/iOS/TDataMaster.embeddedframework.zip", "")); 
				PublicAdditionalFrameworks.Add(new UEBuildFramework("TDMIDFA", "lib/iOS/TDMIDFA.embeddedframework.zip", ""));
				PublicAdditionalFrameworks.Add(new UEBuildFramework("TDMASA", "lib/iOS/TDMASA.embeddedframework.zip", ""));
				PublicAdditionalFrameworks.Add(new UEBuildFramework("tgpasimple", "lib/iOS/tgpasimple.embeddedframework.zip", ""));
				PublicAdditionalFrameworks.Add(new UEBuildFramework("TDMQimeiSDK", "lib/iOS/TDMQimeiSDK.embeddedframework.zip", ""));
			#endif
			var libPath = Path.GetFullPath(ModuleDirectory);
            //IOSEnd
            PublicFrameworks.AddRange(new string[] { "CoreTelephony", "AdSupport", "Security", "UIKit", "SystemConfiguration", "AudioToolbox", "Foundation", "WebKit", "iAd"});
            // PublicWeakFrameworks.AddRange(new string[]{"AppTrackingTransparency"});
            PublicAdditionalLibraries.AddRange(new string[] { "z", "c++", "resolv" });
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            string MacThirdPartyDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "./lib/MAC"));
            PublicDelayLoadDLLs.Add(Path.Combine(MacThirdPartyDir, "libTDataMasterDylib.dylib"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            string Win64ThirdPartyDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "./lib/Win64"));
#if UE_4_24_OR_LATER
            PublicSystemLibraryPaths.Add(Win64ThirdPartyDir);
            
#else
            PublicLibraryPaths.Add(Win64ThirdPartyDir);
#endif

            PublicAdditionalLibraries.Add(Path.Combine(Win64ThirdPartyDir, "TDataMaster.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(Win64ThirdPartyDir, "atls.lib"));
        }
    }
}
