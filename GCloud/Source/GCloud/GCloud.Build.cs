// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

public class GCloud : ModuleRules
{
    string GCloudLibPath = string.Empty;
    bool bUseDll  = true;
    
#if WITH_FORWARDED_MODULE_RULES_CTOR
    public GCloud(ReadOnlyTargetRules Target) : base(Target)
#else
    public GCloud(TargetInfo Target)
#endif
    {
        bUseRTTI = true;
        
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

#if UE_4_20_OR_LATER
        // ue 4.20 or later do not need PublicIncludePaths
#else
        PublicIncludePaths.AddRange(
            new string[] {
            "GCloud/Public"
                // ... add public include paths required here ...
        }
        );
#endif	
        PrivateIncludePaths.AddRange(
            new string[] {
            "GCloud/Private",
            // ... add other private include paths required here ...
        }
        );
        
        PublicDependencyModuleNames.AddRange(
            new string[] {
            "Core",
            "Projects"
                // ... add other public dependencies that you statically link with here ...
        }
        );
        
        DynamicallyLoadedModuleNames.AddRange(
            new string[] {
            // ... add any modules that your module loads dynamically here ...
        }
        );
        
#if UE_5_0_OR_LATER
        string PluginPath = ModuleDirectory;
#else
        string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, "..\\");
#endif

        string GCloudThirdPartyDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "../GCloudLib"));
        
        System.Console.WriteLine("-------------- PluginPath = " + PluginPath);
        
        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
            
            string aplPath = Path.Combine(PluginPath, "GCloudSDK_APL.xml");
            System.Console.WriteLine("-------------- AplPath = " + aplPath);
#if UE_4_20_OR_LATER
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", aplPath);
#else
            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", aplPath));
#endif
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS || Target.Platform == UnrealTargetPlatform.Mac)
        {
            PrivateIncludePaths.Add("GCloud/Private/iOS");
            
            PrivateDependencyModuleNames.AddRange(
                new string[]{
                "ApplicationCore"
                    // ... add private dependencies that you statically link with here ...
            }
            );
        }

        if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicIncludePaths.AddRange(new string[] {"Runtime/ApplicationCore/Public/IOS"});
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
#if UE_4_20_OR_LATER
            // Public/Apple not exist.
#else
            PublicIncludePaths.AddRange(new string[] {"Runtime/ApplicationCore/Public/Apple"});
#endif
        }
        

#if UE_5_0_OR_LATER
        if ( Target.Platform == UnrealTargetPlatform.Win64)
#else
        if ( Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
#endif
        {
            //PrivateIncludePaths.Add("GCloudSDK/Private/");
#if UE_4_20_OR_LATER
            //define _GCLOUD_UE_ for GCloudCore Headers file which include "winsock2.h"
            PublicDefinitions.Add("_GCLOUD_UE_=1");
#else
            Definitions.Add("_GCLOUD_UE_=1");
#endif
            
            if(bUseDll)
            {
                string libDir = (Target.Platform == UnrealTargetPlatform.Win64) ? "X86_64" : "X86";
                GCloudLibPath = Path.Combine(GCloudThirdPartyDir, "Win", libDir);
                System.Console.WriteLine("--------------Win GCloudLibPath = " + GCloudLibPath);

                PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "GCloud.lib"));
                PublicDelayLoadDLLs.Add(Path.Combine(GCloudLibPath, "GCloud.dll"));
                
#if UE_4_20_OR_LATER
                RuntimeDependencies.Add("$(BinaryOutputDir)/GCloud.dll", Path.Combine(GCloudLibPath, "GCloud.dll"));
#else
                string binariesDir = Path.Combine(ModuleDirectory, "../../Binaries", Target.Platform.ToString());
                if (!Directory.Exists(binariesDir))
                {
                    Directory.CreateDirectory(binariesDir);
                }
                try
                {
                    File.Copy(Path.Combine(GCloudLibPath, "GCloud.dll"), Path.Combine(binariesDir, "GCloud.dll"), true);
                }
                catch (Exception e)
                {
                    System.Console.WriteLine("copy dll exception,maybe have exists,err=", e.ToString());
                }
                RuntimeDependencies.Add(new RuntimeDependency("$(BinaryOutputDir)/GCloud.dll"));
#endif
            }
            else
            {
                string libDir = (Target.Platform == UnrealTargetPlatform.Win64) ? "X64" : "X86";
                GCloudLibPath = Path.Combine(GCloudThirdPartyDir, libDir);
                System.Console.WriteLine("--------------Win GCloudLibPath = " + GCloudLibPath);
#if UE_4_24_OR_LATER
                PublicSystemLibraryPaths.Add(GCloudLibPath);
#else
                PublicLibraryPaths.Add(GCloudLibPath);
#endif
                PublicAdditionalLibraries.Add("GCloud_static.lib");
#if !UE_4_19_OR_LATER
                PublicAdditionalLibraries.Add("atls.lib");
#endif
            }
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            string ArchDir = "armeabi-v7a";
            //BASE
            string libDir = ("Android/GCloud/libs");
            GCloudLibPath = Path.Combine(Path.Combine(GCloudThirdPartyDir, libDir), ArchDir);
            System.Console.WriteLine("--------------Android GCloudLibPath = " + GCloudLibPath);
#if UE_4_24_OR_LATER
            PublicSystemLibraryPaths.Add(GCloudLibPath);
            PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "libgcloud.so"));
#else
            PublicLibraryPaths.Add(GCloudLibPath);
#endif

            ArchDir = "arm64-v8a";
            GCloudLibPath = Path.Combine(Path.Combine(GCloudThirdPartyDir, libDir), ArchDir);
            System.Console.WriteLine("--------------Android GCloudLibPath = " + GCloudLibPath);
#if UE_4_24_OR_LATER
            PublicSystemLibraryPaths.Add(GCloudLibPath);
            PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "libgcloud.so"));
#else
            PublicLibraryPaths.Add(GCloudLibPath);
#endif

            ArchDir = "x86";
            GCloudLibPath = Path.Combine(Path.Combine(GCloudThirdPartyDir, libDir), ArchDir);
            System.Console.WriteLine("--------------Android GCloudLibPath = " + GCloudLibPath);
#if UE_4_24_OR_LATER
            PublicSystemLibraryPaths.Add(GCloudLibPath);
            PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "libgcloud.so"));
#else
            PublicLibraryPaths.Add(GCloudLibPath);
#endif

            ArchDir = "x86_64";
            GCloudLibPath = Path.Combine(Path.Combine(GCloudThirdPartyDir, libDir), ArchDir);
            System.Console.WriteLine("--------------Android GCloudLibPath = " + GCloudLibPath);
#if UE_4_24_OR_LATER
            PublicSystemLibraryPaths.Add(GCloudLibPath);
            PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "libgcloud.so"));
#else
            PublicLibraryPaths.Add(GCloudLibPath);
#endif
    
#if UE_4_24_OR_LATER
            
#else
            AddGCloudLib(Target, "gcloud");
#endif
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            GCloudLibPath = GCloudThirdPartyDir;
            System.Console.WriteLine("--------------iOS GCloud.Path = " + GCloudLibPath);

#if UE_4_24_OR_LATER
            PublicSystemLibraries.AddRange(
                new string[] {
                "c++","z","c++","z.1.1.3","sqlite3","xml2"
            });
#else
            PublicAdditionalLibraries.AddRange(
                new string[] {
                "c++","z","c++","z.1.1.3","sqlite3","xml2"
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
                "CoreImage",
                "JavaScriptCore"
            });
            
#if UE_4_22_OR_LATER
            PublicAdditionalFrameworks.Add(new Framework("GCloud", "../GCloudLib/iOS/GCloud.embeddedframework.zip"));
#else 
            PublicAdditionalFrameworks.Add(new UEBuildFramework("GCloud", "../GCloudLib/iOS/GCloud.embeddedframework.zip"));
#endif
        }
        
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            GCloudLibPath = Path.Combine(GCloudThirdPartyDir, "Mac/");
            PublicDelayLoadDLLs.Add(Path.Combine(GCloudLibPath, "libGCloud.dylib"));
        }
#if UE_5_0_OR_LATER && ENABLE_GCLOUD_PS5
        else if (Target.Platform == UnrealTargetPlatform.PS5)
        {
            PublicSystemLibraries.AddRange(new string[]
            {
                "ScePosix_stub_weak",
                "SceNetCtl_stub_weak",
                "SceNet_stub_weak",
                "SceHttp_stub_weak",
                "SceSsl_stub_weak"
            });
            
            GCloudLibPath = Path.Combine(GCloudThirdPartyDir, "PS5/");
            System.Console.WriteLine("--------------PS5 GCloudLibPath = " + GCloudLibPath);
            
            PublicSystemLibraryPaths.Add(GCloudLibPath);
            PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "GCloud_stub.a"));
            
            RuntimeDependencies.Add(Path.Combine(GCloudLibPath, "GCloud.prx"));

            PublicDelayLoadDLLs.Add(Path.Combine(GCloudLibPath, "GCloud.prx"));
        }
#endif
#if UE_5_0_OR_LATER && ENABLE_GCLOUD_PS4
        else if (Target.Platform == UnrealTargetPlatform.PS4)
        {
            PublicSystemLibraries.AddRange(new string[]
            {
                "ScePosix_stub_weak",
                "SceNetCtl_stub_weak",
                "SceNet_stub_weak",
                "SceHttp_stub_weak",
                "SceSsl_stub_weak"
            });
            
            GCloudLibPath = Path.Combine(GCloudThirdPartyDir, "PS4/");
            System.Console.WriteLine("--------------PS4 GCloudLibPath = " + GCloudLibPath);
            
            PublicSystemLibraryPaths.Add(GCloudLibPath);
            PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "GCloud_stub.a"));
            
            RuntimeDependencies.Add(Path.Combine(GCloudLibPath, "GCloud.prx"));

            PublicDelayLoadDLLs.Add(Path.Combine(GCloudLibPath, "GCloud.prx"));
        }
#endif
#if UE_5_0_OR_LATER && ENABLE_GCLOUD_XSX
        else if (Target.Platform == UnrealTargetPlatform.XSX)
        {
            GCloudLibPath = Path.Combine(GCloudThirdPartyDir, "XboxSeries/");
            System.Console.WriteLine("--------------XSX GCloudLibPath = " + GCloudLibPath);

            PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "GCloud.lib"));
            PublicDelayLoadDLLs.Add(Path.Combine(GCloudLibPath, "GCloud.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/GCloud.dll", Path.Combine(GCloudLibPath, "GCloud.dll"));
        }
#endif
#if UE_5_0_OR_LATER && ENABLE_GCLOUD_XB1
        else if (Target.Platform == UnrealTargetPlatform.XB1)
        {
            GCloudLibPath = Path.Combine(GCloudThirdPartyDir, "XboxOne/");
            System.Console.WriteLine("--------------XB1 GCloudLibPath = " + GCloudLibPath);

            PublicAdditionalLibraries.Add(Path.Combine(GCloudLibPath, "GCloud.lib"));
            PublicDelayLoadDLLs.Add(Path.Combine(GCloudLibPath, "GCloud.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/GCloud.dll", Path.Combine(GCloudLibPath, "GCloud.dll"));
        }
#endif
        else
        {
            System.Console.WriteLine("-------------- GCloud not support:" + Target.Platform);
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
