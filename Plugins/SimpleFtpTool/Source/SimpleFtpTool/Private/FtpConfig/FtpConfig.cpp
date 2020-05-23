// Fill out your copyright notice in the Description page of Project Settings.

#include "FtpConfig/FtpConfig.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/Paths.h"
#include "GenericPlatform/GenericPlatformFile.h"


UFtpConfig::UFtpConfig()
{
	IPlatformFile& platform = FPlatformFileManager::Get().GetPlatformFile();
	if (CachePath.Path.IsEmpty())
	{
		CachePath.Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir() / TEXT("DepCache"));
		if (!platform.DirectoryExists(*CachePath.Path))
		{
			platform.CreateDirectory(*CachePath.Path);
		}
	}
	
	bShowServerMesg = true;
	
	Suffix = TEXT(".dep");

	InsProjectName = TEXT("ProjOne");
}

