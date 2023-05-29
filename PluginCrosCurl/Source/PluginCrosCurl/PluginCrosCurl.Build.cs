// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class PluginCrosCurl : ModuleRules
{
	public PluginCrosCurl(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

#if UE_4_20_OR_LATER
		// ue 4.20 or later do not need PublicIncludePaths
#else

		PublicIncludePaths.AddRange(
			new string[] {
				"PluginCrosCurl/Public"
				// ... add public include paths required here ...
			}
			);
#endif
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"PluginCrosCurl/Private",
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

		if (Target.Platform == UnrealTargetPlatform.Android) {
			//Add Android
			PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });

#if UE_4_24_OR_LATER
            PublicSystemLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/PluginCrosCurl/libs/armeabi-v7a")));
            PublicSystemLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/PluginCrosCurl/libs/arm64-v8a")));
            PublicSystemLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/PluginCrosCurl/libs/x86")));
            PublicSystemLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/PluginCrosCurl/libs/x86_64")));
#else
            PublicLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/PluginCrosCurl/libs/armeabi-v7a")));
            PublicLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/PluginCrosCurl/libs/arm64-v8a")));
            PublicLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/PluginCrosCurl/libs/x86")));
            PublicLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/PluginCrosCurl/libs/x86_64")));
#endif
			System.Console.WriteLine("--------------Add Android PluginCrosCurl");
			PublicAdditionalLibraries.Add("PluginCrosCurl");

			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);

#if UE_4_20_OR_LATER
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "PluginCrosCurl_UPL.xml"));
#else
			AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "PluginCrosCurl_UPL.xml")));
#endif

            System.Console.WriteLine("PluginCrosCurl APL Path = " + Path.Combine(PluginPath, "PluginCrosCurl_UPL.xml"));
		} else if (Target.Platform == UnrealTargetPlatform.IOS) {
		    var libPath = Path.GetFullPath(ModuleDirectory);
			System.Console.WriteLine("--------------Add iOS PluginCrosCurl:" + libPath);
            //IOSStart not delete
			#if UE_4_22_OR_LATER 
				PublicAdditionalFrameworks.Add(new Framework("PluginCrosCurl", "lib/iOS/PluginCrosCurl/PluginCrosCurl.embeddedframework.zip", "")); 
			#else 
				PublicAdditionalFrameworks.Add(new UEBuildFramework("PluginCrosCurl", "lib/iOS/PluginCrosCurl/PluginCrosCurl.embeddedframework.zip", "")); 
			#endif
			#if UE_4_22_OR_LATER 
				PublicAdditionalFrameworks.Add(new Framework("crosCurl", "lib/iOS/PluginCrosCurl/crosCurl.embeddedframework.zip", "")); 
			#else 
				PublicAdditionalFrameworks.Add(new UEBuildFramework("crosCurl", "lib/iOS/PluginCrosCurl/crosCurl.embeddedframework.zip", "")); 
			#endif
			//IOSEnd
			PublicFrameworks.AddRange(new string[] { "CoreTelephony", "Security", "SystemConfiguration", "Foundation" });
#if UE_4_24_OR_LATER
			PublicSystemLibraries.AddRange(new string[] { "z" });
#else
			PublicAdditionalLibraries.AddRange(new string[] { "z" });
#endif
		} else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			var CrosCurlLibPath = Path.Combine(ModuleDirectory, "lib/Mac/");
			PublicDelayLoadDLLs.Add(Path.Combine(CrosCurlLibPath, "libcrosCurl.dylib"));
		}
	}
}
