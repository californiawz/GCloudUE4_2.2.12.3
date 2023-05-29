// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class GCloudCore : ModuleRules
{
	string GCloudLibPath = string.Empty;
	bool bUseDll = true;
	
	#if WITH_FORWARDED_MODULE_RULES_CTOR
	public GCloudCore(ReadOnlyTargetRules Target) : base(Target)
		#else
		public GCloudCore(TargetInfo Target)
			#endif
	{
		bUseRTTI = true;
		
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
#if UE_4_20_OR_LATER
		// ue 4.20 or later do not need PublicIncludePaths
#else
		PublicIncludePaths.AddRange(
			new string[] {
			"GCloudCore/Public"
				// ... add public include paths required here ...
		}
		);
#endif
		
		PrivateIncludePaths.AddRange(
			new string[] {
			"GCloudCore/Private",
			// ... add other private include paths required here ...
		}
		);
		
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
			"Core",
			"Projects"
				// ... add other public dependencies that you statically link with here ...
		}
		);
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			// ... add any modules that your module loads dynamically here ...
		}
		);
		
		
#if UE_4_27_OR_LATER
		System.Console.WriteLine("=====UE_4_27_OR_LATER");
		string PluginPath = ModuleDirectory;
#else
		System.Console.WriteLine("=====not UE_4_27_OR_LATER");
		string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, "..\\");
#endif

		PublicIncludePaths.AddRange(new string[] {Path.GetFullPath(Path.Combine(ModuleDirectory, "Public/GCloudCore"))});
		
		string GCloudThirdPartyDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "../GCloudCoreLib"));
		
		System.Console.WriteLine("-------------- PluginPath = " + PluginPath);
		
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
			
			string aplPath = Path.Combine(PluginPath, "GCloudCore_APL.xml");
			System.Console.WriteLine("-------------- AplPath = " + aplPath);
#if UE_4_20_OR_LATER
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", aplPath);
#else
			AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", aplPath));
#endif
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS || Target.Platform == UnrealTargetPlatform.Mac)
		{
			PrivateIncludePaths.Add("GCloudCore/Private/iOS");
			
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
				"ApplicationCore"
					// ... add private dependencies that you statically link with here ...
			}
			);
		}
		
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			string ArchDir = "armeabi-v7a";
			//BASE
			string libDir = ("Android/GCloudCore/libs");
			GCloudLibPath = Path.Combine(Path.Combine(GCloudThirdPartyDir, libDir), ArchDir);
			System.Console.WriteLine("--------------Android GCloudLibPath = " + GCloudLibPath);
#if UE_4_24_OR_LATER
			PublicSystemLibraryPaths.Add(GCloudLibPath);
			PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "libgcloudcore.so"));
#else
			PublicLibraryPaths.Add(GCloudLibPath);
#endif
			

			ArchDir = "arm64-v8a";
			GCloudLibPath = Path.Combine(Path.Combine(GCloudThirdPartyDir, libDir), ArchDir);
			System.Console.WriteLine("--------------Android GCloudLibPath = " + GCloudLibPath);
#if UE_4_24_OR_LATER
			PublicSystemLibraryPaths.Add(GCloudLibPath);
			PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "libgcloudcore.so"));
#else
			PublicLibraryPaths.Add(GCloudLibPath);
#endif

			ArchDir = "x86";
			GCloudLibPath = Path.Combine(Path.Combine(GCloudThirdPartyDir, libDir), ArchDir);
			System.Console.WriteLine("--------------Android GCloudLibPath = " + GCloudLibPath);
#if UE_4_24_OR_LATER
			PublicSystemLibraryPaths.Add(GCloudLibPath);
			PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "libgcloudcore.so"));
#else
			PublicLibraryPaths.Add(GCloudLibPath);
#endif

			ArchDir = "x86_64";
			GCloudLibPath = Path.Combine(Path.Combine(GCloudThirdPartyDir, libDir), ArchDir);
			System.Console.WriteLine("--------------Android GCloudLibPath = " + GCloudLibPath);
#if UE_4_24_OR_LATER
			PublicSystemLibraryPaths.Add(GCloudLibPath);
			PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "libgcloudcore.so"));
#else
			PublicLibraryPaths.Add(GCloudLibPath);
#endif

#if UE_4_24_OR_LATER
			
#else
			AddGCloudLib(Target, "gcloudcore");
#endif
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PublicIncludePaths.AddRange(new string[] {"Runtime/ApplicationCore/Public/IOS"});
			//Definitions.Add("EXTEND_OPENURL=1");
			GCloudLibPath = GCloudThirdPartyDir;
			System.Console.WriteLine("--------------iOS GCloudLibPath = " + GCloudLibPath);
			
#if UE_4_24_OR_LATER
			PublicSystemLibraries.AddRange(
				new string[] {
				"z","c++","z.1.1.3","sqlite3","xml2"
			});
#else
			PublicAdditionalLibraries.AddRange(
				new string[] {
				"z","c++","z.1.1.3","sqlite3","xml2"
			});
#endif

			// These are iOS system libraries that Facebook depends on (FBAudienceNetwork, FBNotifications)
			PublicFrameworks.AddRange(
				new string[] {
				"CoreTelephony",
				"Foundation",
				"MobileCoreServices",
				"CoreData",
				"CoreText",
				"Security",
				"ImageIO",
				"StoreKit",
				"JavaScriptCore",
				"CFNetwork"
			});
			#if UE_4_22_OR_LATER
				PublicAdditionalFrameworks.Add(new Framework("GCloudCore", "../GCloudCoreLib/iOS/GCloudCore.embeddedframework.zip", "Frameworks"));
			#else 
				PublicAdditionalFrameworks.Add(new UEBuildFramework("GCloudCore", "../GCloudCoreLib/iOS/GCloudCore.embeddedframework.zip", "Frameworks"));
			#endif
			

		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
#if UE_4_20_OR_LATER
		// ue 4.21 or later do not have Public/Apple
#else
			PublicIncludePaths.AddRange(new string[] {"Runtime/ApplicationCore/Public/Apple"});
#endif
			GCloudLibPath = Path.Combine(GCloudThirdPartyDir, "Mac/");
			System.Console.WriteLine("--------------Mac GCloudLibPath = " + GCloudLibPath);
			PublicDelayLoadDLLs.Add(Path.Combine(GCloudLibPath, "libGCloudCore.dylib"));
#if UE_4_22_OR_LATER
			System.Console.WriteLine("--------------Mac RuntimeDependencies add GCloudLibPath = " + GCloudLibPath);
			RuntimeDependencies.Add("$(BinaryOutputDir)/libGCloudCore.dylib", Path.Combine(GCloudLibPath, "libGCloudCore.dylib"));
#endif
		}
		else if (
		#if UE_5_0_OR_LATER
		#else
			Target.Platform == UnrealTargetPlatform.Win32 || 
		#endif
			Target.Platform == UnrealTargetPlatform.Win64)
		{
#if UE_4_20_OR_LATER
		    //define _GCLOUDCORE_UE for GCloudCore Headers file which include "winsock2.h"
            PublicDefinitions.Add("_GCLOUDCORE_UE=1");
#else
            Definitions.Add("_GCLOUDCORE_UE=1");
#endif

			if(bUseDll)
			{
				string libDir = (Target.Platform == UnrealTargetPlatform.Win64) ? "X86_64" : "X86";
				GCloudLibPath = Path.Combine(GCloudThirdPartyDir, "Win", libDir);
				System.Console.WriteLine("--------------Win GCloudLibPath = " + GCloudLibPath);

                PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "GCloudCore.lib"));
                PublicDelayLoadDLLs.Add(Path.Combine(GCloudLibPath, "GCloudCore.dll"));

#if UE_4_20_OR_LATER
                RuntimeDependencies.Add("$(BinaryOutputDir)/GCloudCore.dll", Path.Combine(GCloudLibPath, "GCloudCore.dll"));
#else
                string binariesDir = Path.Combine(ModuleDirectory, "../../Binaries", Target.Platform.ToString());
                if (!Directory.Exists(binariesDir))
                {
                    Directory.CreateDirectory(binariesDir);
                }
                try
                {
                    File.Copy(Path.Combine(GCloudLibPath, "GCloudCore.dll"), Path.Combine(binariesDir, "GCloudCore.dll"), true);
                }
                catch (Exception e)
                {
                    System.Console.WriteLine("copy dll exception,maybe have exists,err=", e.ToString());
                }
                RuntimeDependencies.Add(new RuntimeDependency("$(BinaryOutputDir)/GCloudCore.dll"));
#endif
			}
			else
			{
				string libDir = (Target.Platform == UnrealTargetPlatform.Win64) ? "X64" : "X86";//NOTE: only support X64(win64)
				GCloudLibPath = Path.Combine(GCloudThirdPartyDir, libDir);
				System.Console.WriteLine("--------------Win GCloudLibPath = " + GCloudLibPath);
#if UE_4_24_OR_LATER
				PublicSystemLibraryPaths.Add(GCloudLibPath);
#else
				PublicLibraryPaths.Add(GCloudLibPath);
#endif
				PublicAdditionalLibraries.Add("GCloudCore_static.lib");
			}

		}

	}
	
	
	#if WITH_FORWARDED_MODULE_RULES_CTOR
	private void AddGCloudLib(ReadOnlyTargetRules Target, string in_libName)
	#else
	private void AddGCloudLib(TargetInfo Target, string in_libName)
			#endif
	{
		if (Target.Platform == UnrealTargetPlatform.Android || Target.Platform == UnrealTargetPlatform.Linux || Target.Platform == UnrealTargetPlatform.IOS)
		{
			PublicAdditionalLibraries.Add(in_libName);
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
		}
		else
		{
			PublicAdditionalLibraries.Add(in_libName + ".lib");
		}
	}
}
