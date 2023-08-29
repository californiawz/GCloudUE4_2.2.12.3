// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;

public class MSDKPIXCore : ModuleRules
{
	public MSDKPIXCore(ReadOnlyTargetRules Target) : base(Target)
	{
		Environment.SetEnvironmentVariable("MSDK_CORE_NAME", "MSDKPIXCore");

		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

#if UE_4_20_OR_LATER
		// ue 4.20 or later do not need PublicIncludePaths
#else

		PublicIncludePaths.AddRange(
			new string[] {
				"MSDKPIXCore/Public"
				// ... add public include paths required here ...
			}
			);
#endif


		PrivateIncludePaths.AddRange(
			new string[] {
				"MSDKPIXCore/Private",
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
				"HTTP",
				"Json",
				"JsonUtilities",
				"Projects"
			}
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
#if UE_4_20_OR_LATER
        PublicDefinitions.Add("MSDK_CORE=1");
#else
		Definitions.Add("MSDK_CORE=1");
#endif
		//Delete pthread files build for PC to prevent the conflict with the Mobile platform
		System.Console.WriteLine("--------------Delete pthread&sched&semaphore");
		string pcHeadersDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "Public"));
		string pthreadHeaderPath = Path.GetFullPath(Path.Combine(pcHeadersDir, "pthread.h"));
		string schedHeaderPath = Path.GetFullPath(Path.Combine(pcHeadersDir, "sched.h"));
		string semaphoreHeaderPath = Path.GetFullPath(Path.Combine(pcHeadersDir, "semaphore.h"));
		try {
				if (File.Exists(pthreadHeaderPath)) {
					System.Console.WriteLine("Delete pthread.h");
					//File.Delete(pthreadHeaderPath);
				}

				if (File.Exists(schedHeaderPath)) {
					System.Console.WriteLine("Delete sched.h");
					//File.Delete(schedHeaderPath);
				}

				if (File.Exists(semaphoreHeaderPath)) {
					System.Console.WriteLine("Delete semaphore.h");
					//File.Delete(semaphoreHeaderPath);
				}
			} catch (IOException e) {
				System.Console.WriteLine("Delete pthread or sched or semaphore exception, err=", e.ToString());
		}

		if (Target.Platform == UnrealTargetPlatform.Android) {
			//Add Android
			PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
#if UE_4_24_OR_LATER
            PublicSystemLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/msdkpix-core/libs/armeabi-v7a")));
            PublicSystemLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/msdkpix-core/libs/arm64-v8a")));
            PublicSystemLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/msdkpix-core/libs/x86")));
            PublicSystemLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/msdkpix-core/libs/x86_64")));
#else
            PublicLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/msdkpix-core/libs/armeabi-v7a")));
            PublicLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/msdkpix-core/libs/arm64-v8a")));
            PublicLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/msdkpix-core/libs/x86")));
            PublicLibraryPaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "lib/Android/msdkpix-core/libs/x86_64")));
#endif
			System.Console.WriteLine("--------------Add Android MSDKPIXCore");
			PublicAdditionalLibraries.Add("MSDKPIXCore");
			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
#if UE_4_20_OR_LATER
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "MSDKPIXCore_UPL.xml"));
#else
			AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "MSDKPIXCore_UPL.xml")));
#endif
            System.Console.WriteLine("MSDK APL Path = " + Path.Combine(PluginPath, "MSDKPIXCore_UPL.xml"));
		} else if (Target.Platform == UnrealTargetPlatform.IOS) {
			System.Console.WriteLine("--------------Add iOS MSDKPIXPlugin");
            //IOSStart not delete
			#if UE_4_22_OR_LATER 
				PublicAdditionalFrameworks.Add(new Framework("MSDKPIXCore", "lib/iOS/MSDKPIXCore/MSDKPIXCore.embeddedframework.zip", "MSDKAppSetting.bundle")); 
			#else 
				PublicAdditionalFrameworks.Add(new UEBuildFramework("MSDKPIXCore", "lib/iOS/MSDKPIXCore/MSDKPIXCore.embeddedframework.zip", "MSDKAppSetting.bundle")); 
			#endif
			#if UE_4_22_OR_LATER 
				PublicAdditionalFrameworks.Add(new Framework("MSDKPIXSensitivity", "lib/iOS/MSDKPIXCore/MSDKPIXSensitivity.embeddedframework.zip", "")); 
			#else 
				PublicAdditionalFrameworks.Add(new UEBuildFramework("MSDKPIXSensitivity", "lib/iOS/MSDKPIXCore/MSDKPIXSensitivity.embeddedframework.zip", "")); 
			#endif
			#if UE_4_22_OR_LATER 
				PublicAdditionalFrameworks.Add(new Framework("MSDKPopup", "lib/iOS/Third/MSDKPIXCore/MSDKPopup.embeddedframework.zip", "MSDKPopupResource.bundle")); 
			#else 
				PublicAdditionalFrameworks.Add(new UEBuildFramework("MSDKPopup", "lib/iOS/Third/MSDKPIXCore/MSDKPopup.embeddedframework.zip", "MSDKPopupResource.bundle")); 
			#endif
			#if UE_4_22_OR_LATER 
				PublicAdditionalFrameworks.Add(new Framework("MSDKPolicy", "lib/iOS/Third/MSDKPIXCore/MSDKPolicy.embeddedframework.zip", "")); 
			#else 
				PublicAdditionalFrameworks.Add(new UEBuildFramework("MSDKPolicy", "lib/iOS/Third/MSDKPIXCore/MSDKPolicy.embeddedframework.zip", "")); 
			#endif
			//IOSEnd
			PublicFrameworks.AddRange(new string[] { "CoreTelephony", "AdSupport", "Security", "GameKit", "UserNotifications", "WebKit", "UIKit", "SystemConfiguration", "AudioToolbox", "Foundation", "CoreMedia" });
#if UE_4_24_OR_LATER
			PublicSystemLibraries.AddRange(new string[] { "z", "sqlite3", "stdc++", "c++" });
#else
			PublicAdditionalLibraries.AddRange(new string[] { "z", "sqlite3", "stdc++", "c++" });
#endif
		} else if (Target.Platform == UnrealTargetPlatform.Win64) {
            System.Console.WriteLine("--------------TODO: Add Win MSDKPlugin");
			System.Console.WriteLine("--------------Make pthread&sched&semaphore&MSDKCore.cpp");
			string tempPthreadHeaderPath = Path.GetFullPath(Path.Combine(pcHeadersDir, ".msdk_pthread"));
			string tempSchedHeaderPath = Path.GetFullPath(Path.Combine(pcHeadersDir, ".msdk_sched"));
			string tempSemaphoreHeaderPath = Path.GetFullPath(Path.Combine(pcHeadersDir, ".msdk_semaphore"));
			string msdkCoreCppDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "Private"));

			try {
					if (File.Exists(tempPthreadHeaderPath)) {
						System.Console.WriteLine("Make pthread.h");
						File.Copy(tempPthreadHeaderPath, pthreadHeaderPath, false);
					}

					if (File.Exists(tempSchedHeaderPath)) {
						System.Console.WriteLine("Make sched.h");
						File.Copy(tempSchedHeaderPath, schedHeaderPath, false);
					}

					if (File.Exists(tempSemaphoreHeaderPath)) {
						System.Console.WriteLine("Make semaphore.h");
						File.Copy(tempSemaphoreHeaderPath, semaphoreHeaderPath, false);
					}

			} catch (IOException e) {
					System.Console.WriteLine("Make pthread or sched or semaphore or MSDKCore.cpp exception, err=" + e.ToString());
			}
		}
	}
}
