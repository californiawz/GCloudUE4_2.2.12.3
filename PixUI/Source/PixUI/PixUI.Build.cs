// Some copyright should be here...
using System;
using System.IO;
using System.Collections.Generic;
using UnrealBuildTool;

public class PixUI : ModuleRules
{
    private string ModulePath
    {
        get
        {
            return ModuleDirectory;
        }
    }

    public PixUI(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
#if UE_4_21_OR_LATER
        bool bUseUnity = false;  
#endif  //UE_4_21_OR_LATER   
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "ApplicationCore",
                "InputCore",
                "RHI",
                
                // add other public dependencies that you statically link with here ...
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UMG",
                "ImageCore",
                "ImageWrapper",
                "RenderCore",
                "Projects",
                "HTTP",
                "WebSockets"
                // add private dependencies that you statically link with here ...    
            }
        );

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // add any modules that your module loads dynamically here ...
            }
        );

        if (Target.Type == TargetRules.TargetType.Editor)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[] 
                {
                    "UnrealEd",
                    "DesktopPlatform"
                }
            );
        }

        //////////////////////////////////////////////
        ///be unity cpp file for build

        //////////////////////////////////////////////

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //for configure

        //is support paper2d sprite
        bool b_support_paper2d_sprite = true;

        //is support dynamic load library; Whether to use the dynamically loading library files(android-*.so  windows-*.dll  Mac-*.dylib)
        bool b_dynamic_load_library = true;

        // is support bundle copy for framework; 4.25 or before4.25 do not support dynamic framework for IOS
        bool b_use_bundle_copy = false;  //use bundle copy or not 

        //main lib name
        string pxlibName = "PxKit";

        //video lib name
        string px_video_lib_name = "PixVideo";

        //extffi lib name
        string px_extffi_lib_name = "PxExtFFi";
        
        //extobjc lib name
        string px_extobjc_lib_name = "PxExtObjc";
        
        //extffi aar name
        string px_extjava_aar_name = "PxExtJava";

        string px_extjava_arr_version = "0.2.15_release_h_0.1.3_t_0.1.9";

        string px_extjava_arr_full_name = px_extjava_aar_name;  //+ "_" + px_extjava_arr_version;

        //px embedded arr name
        string px_embedded_name = "PxEmbedded";

        //binaries lib name
        string px_binaries_lib_name = "PixUI";


        //cros cul name
        string px_cros_curl_lib_name = "crosCurl";

        string[] cros_curl_depends_dll_names = new string[] {
            "libcrypto-1_1-x64.dll",
            "libssl-1_1-x64.dll",
            "lib" + px_cros_curl_lib_name + ".dll"
        };
        bool b_support_cros_curl = false;

        //GPixUI;
        string px_gpixui_lib_name = "GPixUI";
        bool b_support_gpixui = false;


        bool b_support_px_curl = false;

        //curl lib name
        string pxCurlName = "pixuiCurl";


        bool b_in_pure_pixui = false;  //only for android / ios

        bool b_force_pure_pixui = false;
        bool b_fore_not_pure_pixui = false;

        //video dll names for windows
        string[] video_depends_dll_names = new string[] {
            "avcodec-57.dll",
            "avdevice-57.dll",
            "avfilter-6.dll",
            "avformat-57.dll",
            "avutil-55.dll",
            "libwinpthread-1.dll",
            "pthreadVC2.dll",
            "swresample-2.dll",
            "swscale-4.dll",
            "xaudio2_9redist.dll",
            px_video_lib_name + ".dll"
        };

        //base dll names for windows
        string[] base_dll_names = new string[] {
            pxlibName + ".dll"
        };

        //pfbs
        bool b_support_pfbs = false;

        string px_pfbs_file_name = "pfbs";

        //external file names for windows
        string[] external_file_names = new string[] {
            //"pfbs.exe"
        };


        //mac dll file
        if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            video_depends_dll_names = new string[] {

            };

            base_dll_names = new string[] {
                "lib" + pxlibName + ".dylib"
            };

            external_file_names = new string[] {
                //"pfbs"
            };

            cros_curl_depends_dll_names = new string[] {
                "lib" + px_cros_curl_lib_name + ".dylib"
            };
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //global var
        //is plugin binaries
        bool b_binaries_plugin = false;

        //is support video
        bool b_support_video = false;

        //is support extjava
        bool b_support_extjava = false;
        
        //is support extobjc
        bool b_support_extobjc = false;

        //is support extffi
        bool b_support_extffi = false;

        //is support embedded
        bool b_support_embedded = false;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        //System.Console.WriteLine("build ModulePath ----- :" + ModulePath);
        string basePath = Path.GetDirectoryName(RulesCompiler.GetFileNameFromType(GetType()));

        System.Console.WriteLine("PixUI ModulePath basePath           ----- : " + basePath);

        string thirdPartyPath = Path.Combine(basePath, "ThirdParty"); //Path.GetFullPath(Path.Combine(basePath, "ThirdParty"));
        string fullthirdPartyPath = Path.GetFullPath(Path.Combine(basePath, "ThirdParty"));
                
        System.Console.WriteLine("PixUI ModulePath thirdPartyPath     ----- : " + thirdPartyPath);
        System.Console.WriteLine("PixUI ModulePath fullthirdPartyPath ----- : " + fullthirdPartyPath);

        string binariesPath = Path.GetFullPath(Path.Combine(basePath, "..", "..", "Binaries"));

        if (!Directory.Exists(binariesPath))
        {
            Directory.CreateDirectory(binariesPath);
        }

        //add includes
        string includePath = Path.Combine(thirdPartyPath, "Includes");
#if UE_4_21_OR_LATER
        if(bUseUnity)
        {
            includePath = "PixUI/ThirdParty/Includes";
        }
#endif
        PublicIncludePaths.AddRange(
            new string[] {
                //add public include paths required here ...
                includePath
            }
        );

        if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            //ios do not support dynamic load library
            b_dynamic_load_library = false;
        }
        
        if (b_dynamic_load_library)
        {
#if UE_4_19_OR_LATER
            PublicDefinitions.Add("DF_DY_LOAD_PX=1");
#else
            Definitions.Add("DF_DY_LOAD_PX=1");
#endif  //UE_4_19_OR_LATER
        }
        else
        {
#if UE_4_19_OR_LATER
            PublicDefinitions.Add("DF_DY_LOAD_PX=0");
#else
            Definitions.Add("DF_DY_LOAD_PX=0");
#endif  //UE_4_19_OR_LATER
        }

        {
            //Automatically identify whether in pixui
            string devProjectDir = Path.GetFullPath(Path.Combine(basePath, "..", "..", "..", "GCloudCore"));
            if (Directory.Exists(devProjectDir))
            {
                b_in_pure_pixui = false;
            }
            else 
            {
                b_in_pure_pixui = true;
            }
            System.Console.WriteLine("PixUI Env Automatically             ----- : " + (b_in_pure_pixui ? "in pure pixui" : "not in pure pixui"));
        }

        if (b_force_pure_pixui)
        {
            b_in_pure_pixui = true;
        }

        if (b_fore_not_pure_pixui)
        {
            b_in_pure_pixui = false;
        }

        if (b_force_pure_pixui && b_fore_not_pure_pixui)
        {
            System.Console.WriteLine("PixUI warning b_force_pure_pixui and b_fore_not_pure_pixui all set true and b_in_pure_pixui set to ----- : " + b_in_pure_pixui);
        }

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            //for video
	        if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", "arm64-v8a", "lib" + px_video_lib_name+ ".so")) &&
	            File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", "armeabi-v7a", "lib" + px_video_lib_name + ".so")))
	        {
		        b_support_video = true;
	        }

            //for px curl
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", "arm64-v8a", "lib" + pxCurlName + ".so")) &&
                File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", "armeabi-v7a", "lib" + pxCurlName + ".so")))
            {
                b_support_px_curl = true;
            }

            //for cros curl
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", "arm64-v8a", "lib" + px_cros_curl_lib_name + ".so")) &&
                File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", "armeabi-v7a", "lib" + px_cros_curl_lib_name + ".so")))
            {
                b_support_cros_curl = true;
            }

            //for GPixUI
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", "arm64-v8a", "lib" + px_gpixui_lib_name + ".so")) &&
                File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", "armeabi-v7a", "lib" + px_gpixui_lib_name + ".so")))
            {
                b_support_gpixui = true;
            }

            //for ext ffi
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", "arm64-v8a", "lib" + px_extffi_lib_name+ ".so")) &&
                File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", "armeabi-v7a", "lib" + px_extffi_lib_name + ".so")))
            {
                b_support_extffi = true;
            }

            bool b_extJavaAAr = false;
            //for ext java
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", px_extjava_arr_full_name + ".aar")))
            {
                b_support_extjava = true;
                b_extJavaAAr = true;
            }
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", px_extjava_arr_full_name + ".jar")))
            {
                b_extJavaAAr = false;
                b_support_extjava = true;
            }

            bool b_embeddedAAr = false;
            //for embedded
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", px_embedded_name + ".aar")))
            {
                b_embeddedAAr = true;
                b_support_embedded = true;
            }
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Android", px_embedded_name + ".jar")))
            {
                b_embeddedAAr = false;
                b_support_embedded = true;
            }

            //for binaries
            if (File.Exists(Path.Combine(binariesPath, "Android", "arm64-v8a", "lib" + px_binaries_lib_name + ".a")) &&
	            File.Exists(Path.Combine(binariesPath, "Android", "armeabi-v7a", "lib" + px_binaries_lib_name + ".a")))
	        {
		        b_binaries_plugin = true;
	        }

	        //android jni
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });

            if (!b_dynamic_load_library)
            {
                //Add library path,just support v7a v8a x86
#if UE_4_24_OR_LATER
                PublicSystemLibraryPaths.Add(Path.Combine(thirdPartyPath, "Libraries", "Android", "armeabi-v7a"));
                PublicSystemLibraryPaths.Add(Path.Combine(thirdPartyPath, "Libraries", "Android", "arm64-v8a"));
                //PublicSystemLibraryPaths.Add(Path.Combine(thirdPartyPath, "Libraries", "Android", "armeabi"));
                //PublicSystemLibraryPaths.Add(Path.Combine(thirdPartyPath, "Libraries", "Android", "x86"));

                PublicSystemLibraries.Add(pxlibName);
#else
                PublicLibraryPaths.Add(Path.Combine(thirdPartyPath, "Libraries", "Android", "armeabi-v7a"));
                PublicLibraryPaths.Add(Path.Combine(thirdPartyPath, "Libraries", "Android", "arm64-v8a"));
                //PublicLibraryPaths.Add(Path.Combine(thirdPartyPath, "Libraries", "Android", "armeabi"));
                //PublicLibraryPaths.Add(Path.Combine(thirdPartyPath, "Libraries", "Android", "x86"));

                PublicAdditionalLibraries.Add(pxlibName);
#endif  //UE_4_24_OR_LATER
            }
	
			//is plugin binaries
			if (b_binaries_plugin)
			{
#if UE_4_24_OR_LATER
                PublicSystemLibraryPaths.Add(Path.Combine(basePath, "..", "..", "Binaries", "Android", "armeabi-v7a"));
                PublicSystemLibraryPaths.Add(Path.Combine(basePath, "..", "..", "Binaries", "Android", "arm64-v8a"));

                //PublicSystemLibraryPaths.Add(Path.Combine(basePath, "..", "..", "Binaries", "Android", "armeabi"));
                //PublicSystemLibraryPaths.Add(Path.Combine(basePath, "..", "..", "Binaries", "Android", "x86"));

                PublicSystemLibraries.Add(px_binaries_lib_name);
#else
                PublicLibraryPaths.Add(Path.Combine(basePath, "..", "..", "Binaries", "Android", "armeabi-v7a"));
                PublicLibraryPaths.Add(Path.Combine(basePath, "..", "..", "Binaries", "Android", "arm64-v8a"));
                //PublicLibraryPaths.Add(Path.Combine(basePath, "..", "..", "Binaries", "Android", "armeabi"));
                //PublicLibraryPaths.Add(Path.Combine(basePath, "..", "..", "Binaries", "Android", "x86"));

                PublicAdditionalLibraries.Add(px_binaries_lib_name);
#endif  //UE_4_24_OR_LATER
			}


            //android apl
            {
                List<string> str_android_apl_file = new List<string>();

                //for base pixui
                str_android_apl_file.Add("PixUIPlugin_Android_APL.xml");

                //for video
                if (b_support_video)
                {
                    str_android_apl_file.Add("PixUIPlugin_Android_APL_video.xml");
                }

                //for px curl
                if (b_support_px_curl)
                {
                    str_android_apl_file.Add("PixUIPlugin_Android_APL_pixuiCurl.xml");
                }

                //for cros curl
                if (b_support_cros_curl)
                {
                    str_android_apl_file.Add("PixUIPlugin_Android_APL_crosCurl.xml");
                }

                //for GPixui
                if (b_support_gpixui)
                {
                    str_android_apl_file.Add("PixUIPlugin_Android_APL_GPixUI.xml");
                }

                //for extjava
                if (b_support_extjava)
                {
                    if (b_extJavaAAr)
                    {
                        str_android_apl_file.Add("PixUIPlugin_Android_APL_ExtJava_aar.xml");
                    }
                    else
                    {
                        str_android_apl_file.Add("PixUIPlugin_Android_APL_ExtJava_jar.xml");
                    }
                }

                //for extffi
                if (b_support_extffi)
                {
                    str_android_apl_file.Add("PixUIPlugin_Android_APL_ExtFFI.xml");
                }

                //for embedded
                if(b_support_embedded)
                {
                    if (b_embeddedAAr)
                    {
                        str_android_apl_file.Add("PixUIPlugin_Android_APL_Embedded_aar.xml");
                    }
                    else
                    {
                        str_android_apl_file.Add("PixUIPlugin_Android_APL_Embedded_jar.xml");
                    }
                    
                }

                str_android_apl_file.ForEach(ApiFile =>
                {
                    //add apl file
                    string RelAPLPath = Utils.MakePathRelativeTo(System.IO.Path.Combine(thirdPartyPath, ApiFile),
                            Target.RelativeEnginePath);
#if UE_4_19_OR_LATER
                    AdditionalPropertiesForReceipt.Add("AndroidPlugin", RelAPLPath);
#else
                    AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", RelAPLPath));
#endif  //UE_4_19_OR_LATER
                });
            }
            
            /*
            BuildVersion Version;
            if (BuildVersion.TryRead(out Version))
            {
                if (Version.MajorVersion == X && Version.MinorVersion == Y)
                {
                    // do version specific stuff
                }
            }
            */
            
            //for old version 4.18
            //AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", RelAPLPath));

            //for new version 4.23
            //AdditionalPropertiesForReceipt.Add("AndroidPlugin", RelAPLPath);
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            string PlatformString = "IOS";

            //for video
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString,  px_video_lib_name + ".embeddedframework.zip")))
	        {
		        b_support_video = true;
	        }
            
            //for ffi
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString,  px_extffi_lib_name + ".embeddedframework.zip")))
            {
                b_support_extffi = true;
            }
            
            //for objc
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString,  px_extobjc_lib_name + ".embeddedframework.zip")))
            {
                b_support_extobjc = true;
            }

            //for px curl
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, pxCurlName + ".embeddedframework.zip")))
            {
                b_support_px_curl = true;
            }

            //for cros curl
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, px_cros_curl_lib_name + ".embeddedframework.zip")))
            {
                b_support_cros_curl = true;
            }

            //for GPixUI
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, px_gpixui_lib_name + ".embeddedframework.zip")))
            {
                b_support_gpixui = true;
            }

            //for embedded
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, px_embedded_name + ".embeddedframework.zip")))
            {
                b_support_embedded = true;
            }

            //for binaries
            if (File.Exists(Path.Combine(binariesPath, PlatformString, "lib" + px_binaries_lib_name + ".a")))
	        {
		        b_binaries_plugin = true;
	        }
            //lib path
            string strLibraryPath = Path.Combine(thirdPartyPath, "Libraries", PlatformString);

#if UE_4_24_OR_LATER
            PublicSystemLibraryPaths.Add(strLibraryPath);
#else
            PublicLibraryPaths.Add(strLibraryPath);
#endif  //UE_4_24_OR_LATER


			//is plugin binaries
			if (b_binaries_plugin)
			{
#if UE_4_24_OR_LATER
                PublicSystemLibraryPaths.Add(Path.Combine(basePath, "..", "..", "Binaries", PlatformString));
                PublicSystemLibraries.Add(px_binaries_lib_name);
#else
                PublicLibraryPaths.Add(Path.Combine(basePath, "..", "..", "Binaries", PlatformString));
                PublicAdditionalLibraries.Add(px_binaries_lib_name);
#endif  //UE_4_24_OR_LATER
			}

            bool b_use_static_lib = false;
            if (b_use_static_lib)
            {
                /********************************for static lib************************************************/
                //for ios
                string[] aryLibLoad = new string[] {
                        //"libxxxx.a",
                        "lib"+ pxlibName + ".a"
                    };

                //Binaries
                foreach (string strLibName in aryLibLoad)
                {
#if UE_4_24_OR_LATER
                    PublicSystemLibraries.Add(Path.Combine(strLibraryPath, strLibName));
#else
                    PublicAdditionalLibraries.Add(Path.Combine(strLibraryPath, strLibName));
#endif  //UE_4_24_OR_LATER
                }
                /********************************for static lib************************************************/
            }
            else
            {
                /********************************for .framework lib************************************************/

                //for static framework work fine,but dynamic framework is not

                /*
                string frame_workPath = Path.Combine(strLibraryPath, pxlibName +".embeddedframework.zip");
                PublicAdditionalFrameworks.Add(
                    new UEBuildFramework(
                        pxlibName,
                        frame_workPath)
                );
                */
                strLibraryPath = Path.Combine("ThirdParty", "Libraries", PlatformString);
                List<string> list_dynamicFramework_files = new List<string>();

                //for base pxkit
                list_dynamicFramework_files.Add(pxlibName);

                //for video
                if (b_support_video)
                {
                    list_dynamicFramework_files.Add(px_video_lib_name);
                }

                //for pxembed
                if(b_support_embedded)
                {
                    list_dynamicFramework_files.Add(px_embedded_name);
                }

                //for px curl
                if (b_support_px_curl)
                {
                    list_dynamicFramework_files.Add(pxCurlName);
                }

                //for cros curl
                if (b_support_cros_curl)
                {
                    list_dynamicFramework_files.Add(px_cros_curl_lib_name);
                }

                //for gpixui
                if (b_support_gpixui)
                {
                    list_dynamicFramework_files.Add(px_gpixui_lib_name);
                }

                //for extffi
                if (b_support_extffi)
                {
                    list_dynamicFramework_files.Add(px_extffi_lib_name);
                }

                //for extobjc
                if (b_support_extobjc)
                {
                    list_dynamicFramework_files.Add(px_extobjc_lib_name);
                }

                //need to create Frameworks dir for copy to BuildDir
                string ios_binaries_dir = Path.Combine(binariesPath, PlatformString);
                if (!Directory.Exists(ios_binaries_dir))
                {
                    Directory.CreateDirectory(ios_binaries_dir);
                }

                string ios_frameworks_dir = Path.Combine(ios_binaries_dir, "Frameworks");
                if (!Directory.Exists(ios_frameworks_dir))
                {
                    Directory.CreateDirectory(ios_frameworks_dir);
                }

                Func<string, string> getBundleName = (dynamicFramework =>
                {
                    if (dynamicFramework == px_embedded_name)
                    {
                        return "PxEmbeddedHotUpdate.bundle";
                    }
                    else
                    {
                        return null;
                    }
                });

                list_dynamicFramework_files.ForEach(dynamicFramework =>
                {
                    //for framework
                    string frameworkPath = Path.Combine(strLibraryPath, dynamicFramework + ".embeddedframework.zip");
#if UE_4_26_OR_LATER
                    PublicAdditionalFrameworks.Add(
                        new Framework(
                            dynamicFramework,       //Name
                            frameworkPath,          //ZipFile
                            getBundleName(dynamicFramework),                   //CopyBundledAssets
                            true                    //bCopyFramework
                        )
                    );
#else

#if UE_4_22_OR_LATER
                    string IosUplFile = "PixUIPlugin_IOS_UPL_22_to_25_" + dynamicFramework + ".xml";
                    PublicAdditionalFrameworks.Add(
                            new Framework(
                                dynamicFramework,
                                frameworkPath,          //ZipFile
                                getBundleName(dynamicFramework)
                            )
                        );
#else
                    string IosUplFile = "PixUIPlugin_IOS_UPL_18_to_21_" + dynamicFramework + ".xml";
                    PublicAdditionalFrameworks.Add(
                            new UEBuildFramework(
                                dynamicFramework,
                                frameworkPath,          //ZipFile
                                getBundleName(dynamicFramework)
                            )
                        );
#endif //UE_4_22_OR_LATER
                    //for upl file to copy Framework
                   
#if UE_4_19_OR_LATER
                    //after 4.18
                    AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(thirdPartyPath, IosUplFile));
#else
                    //v4.18 or before4.18
                    string str_Upl_Path = Utils.MakePathRelativeTo(System.IO.Path.Combine(thirdPartyPath, IosUplFile), Target.RelativeEnginePath);
                    AdditionalPropertiesForReceipt.Add(new ReceiptProperty("IOSPlugin", str_Upl_Path));
#endif  //UE_4_19_OR_LATER

#endif //UE_4_26_OR_LATER

                });

                //string video_lib_path = Path.Combine(strLibraryPath, px_video_lib_name + ".embeddedframework.zip");
                //string extffi_lib_path = Path.Combine(strLibraryPath, px_extffi_lib_name + ".embeddedframework.zip");
                //string extobjc_lib_path = Path.Combine(strLibraryPath, px_extobjc_lib_name + ".embeddedframework.zip");
                //string pixui_lib_path = Path.Combine(strLibraryPath, pxlibName +".embeddedframework.zip");
                //string curl_lib_path = Path.Combine(strLibraryPath, pxCurlName +".embeddedframework.zip");
                /********************************for .framework lib************************************************/
            }

            //other system lib
#if UE_4_24_OR_LATER
            PublicSystemLibraries.AddRange(
                new string[] {
                    "z",
                    "c++",
                    "resolv"
            });
#else
            PublicAdditionalLibraries.AddRange(
                new string[] {
                    "z",
                    "c++",
                    "resolv"
            });
#endif  //UE_4_24_OR_LATER

            //add system framewoeks
            PublicFrameworks.AddRange(
                new string[] {
                    "Foundation",
                    "CoreFoundation",
                    "QuartzCore",
                    "Security"
                }
            );
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            string PlatformString = "Mac";

            //mac platform use static video lib,so to check win64 dll file
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", "Win64", px_video_lib_name +".dll")))
	        {
		        b_support_video = true;
	        }

            //check cros curl
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, "lib" + px_cros_curl_lib_name + ".dylib")))
            {
                b_support_cros_curl = true;
            }

            //check px curl
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, pxCurlName + ".dylib")))
            {
                b_support_px_curl = true;
            }

            //check ffi
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, "lib" + px_extffi_lib_name + ".dylib")))
            {
                b_support_extffi = true;
            }

            //check objc
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, "lib" + px_extobjc_lib_name + ".dylib")))
            {
                b_support_extobjc = true;
            }

            //check binaries
            if (File.Exists(Path.Combine(binariesPath, PlatformString, "lib" + px_binaries_lib_name + ".a")))
	        {
		        b_binaries_plugin = true;
	        }

            //check pfbs
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, px_pfbs_file_name)))
            {
                b_support_pfbs = true;
            }

            if (b_binaries_plugin)
            {
#if UE_4_24_OR_LATER
                PublicSystemLibraries.Add(Path.Combine(basePath, "..", "..", "Binaries", PlatformString,"lib" + px_binaries_lib_name + ".a"));
#else
                PublicAdditionalLibraries.Add(Path.Combine(basePath, "..", "..", "Binaries", PlatformString, "lib" + px_binaries_lib_name + ".a"));
#endif  //UE_4_24_OR_LATER
            }

            //be dynamic load library
            if (!b_dynamic_load_library)
            {
                //add lib path
                string LibraryPath = Path.Combine(thirdPartyPath, "Libraries", PlatformString) + "/";

#if UE_4_24_OR_LATER
                PublicSystemLibraryPaths.Add(LibraryPath);
#else
                PublicLibraryPaths.Add(LibraryPath);
#endif //UE_4_24_OR_LATER

                string strDylibName = "lib" + pxlibName + ".dylib";

                //PublicDelayLoadDLLs.Add(strDylibName);
                //RuntimeDependencies.Add(LibraryPath + strDylibName);

                string strDylibPath = Path.Combine(thirdPartyPath, "Libraries", PlatformString, strDylibName);
                //for mac
                //PublicAdditionalLibraries.Add(strDylibPath);
                PublicDelayLoadDLLs.Add(strDylibPath);
                //PublicAdditionalShadowFiles.Add(strDylibPath);
            }

            //pack Mac copy dependencies dylib to Binaries dir
            {
                string lib_binaries_platform = Path.Combine(binariesPath, PlatformString);
                if (!Directory.Exists(lib_binaries_platform))
                {
                    Directory.CreateDirectory(lib_binaries_platform);
                }


                List<string> str_RuntimeDependencies_files = new List<string>();

                //dll RuntimeDependencies
                string libRootPath = Path.Combine(thirdPartyPath, "Libraries", PlatformString);
                string dll_root_path = libRootPath; //Path.Combine(basePath, "..", "..", "Binaries", PlatformString);

                string win_target_path = lib_binaries_platform;

                //for video
                if (b_support_video)
                {
                    foreach (string dllName in video_depends_dll_names)
                    {
                        str_RuntimeDependencies_files.Add(dllName);
                    }
                }

                //base dll
                foreach (string dllName in base_dll_names)
                {
                    str_RuntimeDependencies_files.Add(dllName);
                }

                //external files
                foreach (string dllName in external_file_names)
                {
                    str_RuntimeDependencies_files.Add(dllName);
                }

                //pfbs
                if (b_support_pfbs)
                {
                    str_RuntimeDependencies_files.Add(px_pfbs_file_name);
                }

                //for base curl
                if (b_support_px_curl)
                {
                    str_RuntimeDependencies_files.Add("lib" + pxCurlName + ".dylib");
                }

                //for cros curl
                if (b_support_cros_curl)
                {
                    foreach (string dllName in cros_curl_depends_dll_names)
                    {
                        str_RuntimeDependencies_files.Add(dllName);
                    }
                }

                //for ffi
                if (b_support_extffi)
                {
                    str_RuntimeDependencies_files.Add("lib" + px_extffi_lib_name + ".dylib");
                }

                //for extobjc
                if (b_support_extobjc)
                {
                    str_RuntimeDependencies_files.Add("lib" + px_extobjc_lib_name + ".dylib");
                }


                //all files
                str_RuntimeDependencies_files.ForEach(dllName =>
                {
                    //add apl file
                    string dst_file_path = Path.Combine(win_target_path, dllName);
                    string src_file_path = Path.Combine(dll_root_path, dllName);
                    if (File.Exists(dst_file_path))
                    {
                        File.Delete(dst_file_path);
                    }
                    File.Copy(src_file_path, dst_file_path);
#if UE_4_19_OR_LATER
                    RuntimeDependencies.Add(dst_file_path);
#else
                    RuntimeDependencies.Add(new RuntimeDependency(dst_file_path));
#endif  //UE_4_19_OR_LATER
                });

            }

            //lib
#if UE_4_24_OR_LATER
            PublicSystemLibraries.AddRange(
                new string[] {
                    "z",
                    "c++",
                    "resolv"
            });
#else
            PublicAdditionalLibraries.AddRange(
                new string[] {
                    "z",
                    "c++",
                    "resolv"
            });
#endif  //UE_4_24_OR_LATER

            //add framewoeks
            PublicFrameworks.AddRange(
                new string[] {

                }
            );
        }
#if UE_5_0_OR_LATER
        else if ((Target.Platform == UnrealTargetPlatform.Win64))
#else
        else if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
#endif  //UE_5_0_OR_LATER
        {
            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";

            b_support_video = true;
            //check video lib files
            foreach (string dll_name in video_depends_dll_names)
            {
                if (!File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, dll_name)))
                {
                    b_support_video = false;
                    break;
                }
            }

            //check ffi
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, px_extffi_lib_name + ".dll")))
            {
                b_support_extffi = true;
            }

            //check cros curl
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, "lib" + px_cros_curl_lib_name + ".dll")))
            {
                b_support_cros_curl = true;
            }

            //check px curl
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, pxCurlName + ".dll")))
            {
                b_support_px_curl = true;
            }

            //check pfbs
            if (File.Exists(Path.Combine(fullthirdPartyPath, "Libraries", PlatformString, px_pfbs_file_name + ".exe")))
            {
                b_support_pfbs = true;
            }

            //check binaries lib file
            if (File.Exists(Path.Combine(binariesPath, "Win64", px_binaries_lib_name + ".lib")))
            {
                b_binaries_plugin = true;
            }


            if (b_binaries_plugin)
            {
#if UE_4_24_OR_LATER
                PublicSystemLibraryPaths.Add(Path.Combine(basePath, "..", "..", "Binaries", PlatformString));
                PublicSystemLibraries.Add(px_binaries_lib_name + ".lib");
#else
                PublicLibraryPaths.Add(Path.Combine(basePath, "..", "..", "Binaries", PlatformString));
                PublicAdditionalLibraries.Add(px_binaries_lib_name + ".lib");
#endif  //UE_4_24_OR_LATER
            }

            string libRootPath = Path.Combine(thirdPartyPath, "Libraries", PlatformString);

            //dll RuntimeDependencies
            string dll_root_path = libRootPath; //Path.Combine(basePath, "..", "..", "Binaries", PlatformString);
            //be dynamic load library
            if (!b_dynamic_load_library)
            {
                //lib path
#if UE_4_24_OR_LATER
                PublicSystemLibraryPaths.Add(libRootPath);

                //for libs file
                PublicSystemLibraries.Add(pxlibName + ".lib");
#else
                PublicLibraryPaths.Add(libRootPath);

                //for libs file
                PublicAdditionalLibraries.Add(pxlibName + ".lib");
#endif  //UE_4_24_OR_LATER

                //System.Console.WriteLine("build dll_root_path:" + dll_root_path);
                if (b_support_video)
                {
                    foreach (string dllName in video_depends_dll_names)
                    {
                        PublicDelayLoadDLLs.Add(dllName);
                    }
                }

                //ffi dynamicload by pixui,so do not need PublicDelayLoadDLLs

                //Binaries
                foreach (string dllName in base_dll_names)
                {
                    PublicDelayLoadDLLs.Add(dllName);
                }

                //external files
                foreach (string dllName in external_file_names)
                {
                    //to do
                }

                //for base curl
                if (b_support_px_curl)
                {
                    PublicDelayLoadDLLs.Add(pxCurlName + ".dll");
                }

                //for cros curl
                if (b_support_cros_curl)
                {
                    foreach (string dllName in cros_curl_depends_dll_names)
                    {
                        PublicDelayLoadDLLs.Add(dllName);
                    }
                }
            }

            string lib_binaries_root = Path.Combine(binariesPath, PlatformString);
            if (!Directory.Exists(lib_binaries_root))
            {
                Directory.CreateDirectory(lib_binaries_root);
            }

            //pack windows copy dependencies dll to Binaries dir
            {

                List<string> str_RuntimeDependencies_files = new List<string>();

                string win_target_path = Path.Combine(binariesPath, PlatformString);

                //video dll
                if (b_support_video)
                {
                    foreach (string dllName in video_depends_dll_names)
                    {
                        str_RuntimeDependencies_files.Add(dllName);
                    }
                }

                //base dll
                foreach (string dllName in base_dll_names)
                {
                    str_RuntimeDependencies_files.Add(dllName);
                }

                //external files
                foreach (string dllName in external_file_names)
                {
                    str_RuntimeDependencies_files.Add(dllName);
                }

                if (b_support_pfbs)
                {
                    str_RuntimeDependencies_files.Add(px_pfbs_file_name + ".exe");
                }

                //for base curl
                if (b_support_px_curl)
                {
                    str_RuntimeDependencies_files.Add(pxCurlName + ".dll");
                }

                //for cros curl
                if (b_support_cros_curl)
                {
                    foreach (string dllName in cros_curl_depends_dll_names)
                    {
                        str_RuntimeDependencies_files.Add(dllName);
                    }
                }

                //be support ffi
                if (b_support_extffi)
                {
                    str_RuntimeDependencies_files.Add(px_extffi_lib_name + ".dll");
                }

                //all files
                str_RuntimeDependencies_files.ForEach(dllName =>
                {
                    //add apl file
                    string dst_file_path = Path.Combine(win_target_path, dllName);
                    string src_file_path = Path.Combine(dll_root_path, dllName);
                    if (File.Exists(dst_file_path))
                    {
                        File.Delete(dst_file_path);
                    }
                    File.Copy(src_file_path, dst_file_path);
#if UE_4_19_OR_LATER
                    RuntimeDependencies.Add(dst_file_path);
#else
                    RuntimeDependencies.Add(new RuntimeDependency(dst_file_path));
#endif  //UE_4_19_OR_LATER
                });

                if (!b_in_pure_pixui)
                {
                    var CrosCurlLibPath = Path.Combine(ModuleDirectory, "../../../PluginCrosCurl/Source/PluginCrosCurl/lib/Win64/");
#if UE_4_20_OR_LATER
                    var PixUILibPath = Path.Combine(ModuleDirectory, "ThirdParty/Libraries/Win64/");
                    RuntimeDependencies.Add(Path.Combine(PixUILibPath, "libcrosCurl.dll"), Path.Combine(CrosCurlLibPath, "libcrosCurl.dll"));
                    RuntimeDependencies.Add(Path.Combine(PixUILibPath, "libcrypto-1_1-x64.dll"), Path.Combine(CrosCurlLibPath, "libcrypto-1_1-x64.dll"));
                    RuntimeDependencies.Add(Path.Combine(PixUILibPath, "libssl-1_1-x64.dll"), Path.Combine(CrosCurlLibPath, "libssl-1_1-x64.dll"));
#else
                    string binariesDir = Path.Combine(ModuleDirectory, "ThirdParty/Libraries/Win64/");
                    if (!Directory.Exists(binariesDir))
                    {
                        Directory.CreateDirectory(binariesDir);
                    }
                    try
                    {
                        File.Copy(Path.Combine(CrosCurlLibPath, "libcrosCurl.dll"), Path.Combine(binariesDir, "libcrosCurl.dll"), true);
                        File.Copy(Path.Combine(CrosCurlLibPath, "libcrypto-1_1-x64.dll"), Path.Combine(binariesDir, "libcrypto-1_1-x64.dll"), true);
                        File.Copy(Path.Combine(CrosCurlLibPath, "libssl-1_1-x64.dll"), Path.Combine(binariesDir, "libssl-1_1-x64.dll"), true);
                    }
                    catch (Exception e)
                    {
                        System.Console.WriteLine("pixui copy croscurl dll exception,maybe have exists,err=", e.ToString());
                    }
                    RuntimeDependencies.Add(new RuntimeDependency("$(BinaryOutputDir)/libcrosCurl.dll"));
                    RuntimeDependencies.Add(new RuntimeDependency("$(BinaryOutputDir)/libcrypto-1_1-x64.dll"));
                    RuntimeDependencies.Add(new RuntimeDependency("$(BinaryOutputDir)/libssl-1_1-x64.dll"));
#endif  //UE_4_20_OR_LATER
                }

            }
        }
        
        System.Console.WriteLine("PixUI b_in_pure_pixui               ----- : " + b_in_pure_pixui);

        System.Console.WriteLine("PixUI b_dynamic_load_library        ----- : " + b_dynamic_load_library);
        System.Console.WriteLine("PixUI b_support_video               ----- : " + b_support_video);
        System.Console.WriteLine("PixUI b_support_pfbs                ----- : " + b_support_pfbs);

        if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            System.Console.WriteLine("PixUI b_use_bundle_copy             ----- : " + b_use_bundle_copy);
        }
        System.Console.WriteLine("PixUI b_binaries_plugin             ----- : " + b_binaries_plugin);


        //ffi
        System.Console.WriteLine("PixUI b_support_extffi              ----- : " + b_support_extffi);


        //java
        System.Console.WriteLine("PixUI b_support_extjava             ----- : " + b_support_extjava + " version:" + px_extjava_arr_version);


        //objc
        System.Console.WriteLine("PixUI b_support_extobjc             ----- : " + b_support_extobjc);

        //px curl
        System.Console.WriteLine("PixUI b_support_px_curl             ----- : " + b_support_px_curl);

        //cros curl
        System.Console.WriteLine("PixUI b_support_cros_curl           ----- : " + b_support_cros_curl);

        //GPixUI
        System.Console.WriteLine("PixUI b_support_gpixui              ----- : " + b_support_gpixui);

#if UE_4_21_OR_LATER
	    System.Console.WriteLine("PixUI bUseUnity                     ----- : " + bUseUnity);
#endif  //UE_4_21_OR_LATER  

        if (b_support_video)
        {
#if UE_4_19_OR_LATER
	        PublicDefinitions.Add("DF_PX_WITH_VIDEO=1");
#else
            Definitions.Add("DF_PX_WITH_VIDEO=1");
#endif  //UE_4_19_OR_LATER
        }
        else
        {
#if UE_4_19_OR_LATER
	        PublicDefinitions.Add("DF_PX_WITH_VIDEO=0");
#else
            Definitions.Add("DF_PX_WITH_VIDEO=0");
#endif  //UE_4_19_OR_LATER
        }

        if (b_in_pure_pixui)
        {
#if UE_4_19_OR_LATER
            PublicDefinitions.Add("DF_PX_PURE_ENV=1");
#else
            Definitions.Add("DF_PX_PURE_ENV=1");
#endif  //UE_4_19_OR_LATER
        }
        else
        {
#if UE_4_19_OR_LATER
            PublicDefinitions.Add("DF_PX_PURE_ENV=0");
#else
            Definitions.Add("DF_PX_PURE_ENV=0");
#endif  //UE_4_19_OR_LATER
        }


        if (b_support_px_curl)
        {
#if UE_4_19_OR_LATER
            PublicDefinitions.Add("DF_PX_PX_CURL=1");
#else
            Definitions.Add("DF_PX_PX_CURL=1");
#endif  //UE_4_19_OR_LATER
        }
        else
        {
#if UE_4_19_OR_LATER
            PublicDefinitions.Add("DF_PX_PX_CURL=0");
#else
            Definitions.Add("DF_PX_PX_CURL=0");
#endif  //UE_4_19_OR_LATER
        }


        if (!b_binaries_plugin)
        {
	        PrivateIncludePaths.AddRange(
		        new string[] {
			        //add other private include paths required here ...
			        "PixUI/Private" //4.18 can not auto include this path
		        }
	        );
        }
        if (b_support_paper2d_sprite)
        {
	        PublicDependencyModuleNames.AddRange(
		        new string[]
		        {
			        "Paper2D"
		        }
	        );
#if UE_4_19_OR_LATER
	        PublicDefinitions.Add("DF_SUPPORT_PAPER_SPRITE=1");
#else
            Definitions.Add("DF_SUPPORT_PAPER_SPRITE=1");
#endif  //UE_4_19_OR_LATER
        }
    }
}
