// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Collections.Generic;

public class GVoice : ModuleRules
{
    #if WITH_FORWARDED_MODULE_RULES_CTOR
    	public GVoice(ReadOnlyTargetRules Target) : base(Target)
    #else
        public GVoice(TargetInfo Target)
    #endif
	{
        string GVoiceLibPath = string.Empty;

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
        #if UE_4_20_OR_LATER
                // ue 4.20 or later do not need PublicIncludePaths
        #else
    		PublicIncludePaths.AddRange(
    			new string[] {
    				"GVoice/Public",
    				// ... add public include paths required here ...
    			}
    		);
        #endif
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"GVoice/Private",
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
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
		);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);


        string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
        string GVoiceLibDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "../GVoiceLib/"));

        System.Console.WriteLine("--------------GVoice PluginPath = " + PluginPath);
        System.Console.WriteLine("--------------GVoice GVoiceLibDir = " + GVoiceLibDir);

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });

            string aplPath = Path.Combine(PluginPath, "GVoice_APL.xml");
            System.Console.WriteLine("--------------GVoice AplPath = " + aplPath);
            
            #if UE_4_19_OR_LATER
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", aplPath);
            #else 
                AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", aplPath));
            #endif

        }
        else if (Target.Platform == UnrealTargetPlatform.IOS )
        {

            PrivateIncludePaths.Add("GVoice/Private/IOS");

            #if UE_4_20_OR_LATER
                    // ue 4.20 or later do not need PublicIncludePaths
            #else
                        PublicIncludePaths.AddRange(new string[] {"Runtime/ApplicationCore/Public/Apple", "Runtime/ApplicationCore/Public/IOS"});
            #endif
            
            PrivateDependencyModuleNames.AddRange(
                new string[]{
                    "ApplicationCore"
                    // ... add private dependencies that you statically link with here ...
                }
            );
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {

            #if UE_4_19_OR_LATER
                PublicDefinitions.Add("__GVOICE_MAC__");
            #else
                Definitions.Add("__GVOICE_MAC__");
            #endif
        }

        if (
        #if UE_5_0_OR_LATER
        #else
            Target.Platform == UnrealTargetPlatform.Win32 ||
        #endif
            Target.Platform == UnrealTargetPlatform.Win64)
        {
            PrivateIncludePaths.Add("GVoice/Private/");

        #if UE_5_0_OR_LATER
            string OSVersion = "Win/X86_64";
        #else
            string OSVersion = (Target.Platform == UnrealTargetPlatform.Win32) ? "Win/X86" : "Win/X86_64";
        #endif

            GVoiceLibPath = Path.Combine(GVoiceLibDir, OSVersion);
            Console.WriteLine("GVoiceLibPath:" + GVoiceLibPath);

            string libPath = Path.Combine(GVoiceLibPath, "GVoice.lib");
            PublicAdditionalLibraries.Add(libPath);
            PublicDelayLoadDLLs.Add(Path.Combine(GVoiceLibPath, "GVoice.dll"));
            PublicDelayLoadDLLs.Add(Path.Combine(GVoiceLibPath, "pthreadVC2.dll"));
            
            string binariesDir = Path.Combine(ModuleDirectory, "../../Binaries", Target.Platform.ToString());
            Console.WriteLine("binariesDir:" + binariesDir);

            string dllPath = Path.Combine(GVoiceLibPath, "GVoice.dll");
            System.Console.WriteLine("src dll=" + dllPath + " dst dir=" + binariesDir);
            if (!Directory.Exists(binariesDir))
                Directory.CreateDirectory(binariesDir);
            try
            {
                File.Copy(dllPath, Path.Combine(binariesDir, "GVoice.dll"), true);
            }
            catch (Exception e)
            {
                System.Console.WriteLine("copy dll exception,maybe have exists,err=", e.ToString());
            }

#if UE_4_20_OR_LATER
            RuntimeDependencies.Add("$(BinaryOutputDir)/GVoice.dll", Path.Combine(GVoiceLibPath, "GVoice.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/pthreadVC2.dll", Path.Combine(GVoiceLibPath, "pthreadVC2.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/config.json", Path.Combine(GVoiceLibPath, "config.json"));
#else
            RuntimeDependencies.Add(new RuntimeDependency("$(BinaryOutputDir)/GVoice.dll"));
            RuntimeDependencies.Add(new RuntimeDependency("$(BinaryOutputDir)/pthreadVC2.dll"));
#endif
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            #if UE_4_23_OR_LATER
                //BASE
                string libDir = ("Android/libs");

                string ArchDir = "armeabi-v7a";
                GVoiceLibPath = Path.Combine(Path.Combine(GVoiceLibDir, libDir), ArchDir);
                System.Console.WriteLine("--------------Android GVoiceLibPath = " + GVoiceLibPath);
                string strLib = GVoiceLibPath + "/libGVoice.so";
                AddGVoiceLib(Target, strLib);

                ArchDir = "arm64-v8a";
                GVoiceLibPath = Path.Combine(Path.Combine(GVoiceLibDir, libDir), ArchDir);
                System.Console.WriteLine("--------------Android GVoiceLibPath = " + GVoiceLibPath);
                strLib = GVoiceLibPath + "/libGVoice.so";
                AddGVoiceLib(Target, strLib);

                ArchDir = "x86";
                GVoiceLibPath = Path.Combine(Path.Combine(GVoiceLibDir, libDir), ArchDir);
                System.Console.WriteLine("--------------Android GVoiceLibPath = " + GVoiceLibPath);
                strLib = GVoiceLibPath + "/libGVoice.so";
                AddGVoiceLib(Target, strLib);

                ArchDir = "x86_64";
                GVoiceLibPath = Path.Combine(Path.Combine(GVoiceLibDir, libDir), ArchDir);
                System.Console.WriteLine("--------------Android GVoiceLibPath = " + GVoiceLibPath);

                strLib = GVoiceLibPath + "/libGVoice.so";
                AddGVoiceLib(Target, strLib);
            #else
                string ArchDir = "armeabi-v7a";
                //BASE
                string libDir = ("Android/libs");
                GVoiceLibPath = Path.Combine(Path.Combine(GVoiceLibDir, libDir), ArchDir);
                System.Console.WriteLine("--------------Android GCloudLibPath = " + GVoiceLibPath);
                PublicLibraryPaths.Add(GVoiceLibPath);

                ArchDir = "arm64-v8a";
                GVoiceLibPath = Path.Combine(Path.Combine(GVoiceLibDir, libDir), ArchDir);
                System.Console.WriteLine("--------------Android GCloudLibPath = " + GVoiceLibPath);
                PublicLibraryPaths.Add(GVoiceLibPath);

                ArchDir = "x86";
                GVoiceLibPath = Path.Combine(Path.Combine(GVoiceLibDir, libDir), ArchDir);
                System.Console.WriteLine("--------------Android GCloudLibPath = " + GVoiceLibPath);
                PublicLibraryPaths.Add(GVoiceLibPath);

                ArchDir = "x86_64";
                GVoiceLibPath = Path.Combine(Path.Combine(GVoiceLibDir, libDir), ArchDir);
                System.Console.WriteLine("--------------Android GCloudLibPath = " + GVoiceLibPath);
                PublicLibraryPaths.Add(GVoiceLibPath);

                AddGVoiceLib(Target, "GVoice");
            #endif

        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            GVoiceLibPath = GVoiceLibDir;
            Path.Combine(GVoiceLibPath, "Mac/");
            string strLib = GVoiceLibPath + "/Mac/libGVoice.a";
            PublicAdditionalLibraries.Add(strLib);
            Console.WriteLine("GVoiceLibPath: " + strLib);
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            #if UE_4_22_OR_LATER
                PublicAdditionalFrameworks.Add(new Framework("GVoice_dylib", "../GVoiceLib/iOS/GVoice_dylib.embeddedframework.zip", "GCloudVoice.bundle"));
            #else 
                PublicAdditionalFrameworks.Add(new UEBuildFramework("GVoice_dylib", "../GVoiceLib/iOS/GVoice_dylib.embeddedframework.zip", "GCloudVoice.bundle"));
            #endif

            PublicAdditionalLibraries.AddRange(
            new string[] {
                "c++",
            });
            
            // These are iOS system libraries
            PublicFrameworks.AddRange(
            new string[] {
                "AVFoundation",
                "CoreTelephony",
                "Security",
                "SystemConfiguration",
                "AudioToolbox",
                "CoreAudio",
                "Foundation",
            });
        }

    }


#if WITH_FORWARDED_MODULE_RULES_CTOR
    private void AddGVoiceLib(ReadOnlyTargetRules Target, string in_libName)
#else
    private void AddGVoiceLib(TargetInfo Target, string in_libName)
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

