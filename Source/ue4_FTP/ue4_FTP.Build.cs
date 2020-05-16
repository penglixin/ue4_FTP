// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class ue4_FTP : ModuleRules
{
    //private string FtpThirdPartyPath
    //{
    //    get
    //    {
    //        return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty"));
    //    }
    //}

	public ue4_FTP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","SimpleFtpTool"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });


        //string HFolderPath = Path.Combine(FtpThirdPartyPath, "include");
        //PublicIncludePaths.Add(HFolderPath);
        //PublicIncludePaths.Add(Path.Combine(HFolderPath, "openssl"));

        //string LibPath = Path.Combine(FtpThirdPartyPath, "lib");
        //PublicLibraryPaths.Add(LibPath);
        //PublicAdditionalLibraries.Add(Path.Combine(FtpThirdPartyPath, "lib", "libcurl.lib"));

        //string DLLPath = Path.Combine(FtpThirdPartyPath, "dll");
        //PublicDelayLoadDLLs.Add(Path.Combine(DLLPath, "libcurl.dll"));
        //PublicDelayLoadDLLs.Add(Path.Combine(DLLPath, "libeay32.dll"));
        //PublicDelayLoadDLLs.Add(Path.Combine(DLLPath, "ssleay32.dll"));
        //PublicDelayLoadDLLs.Add(Path.Combine(DLLPath, "weixin.dll"));
        //PublicDelayLoadDLLs.Add(Path.Combine(DLLPath, "zlib.dll"));


    }
}
