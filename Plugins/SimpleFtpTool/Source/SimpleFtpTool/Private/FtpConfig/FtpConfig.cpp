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
		CachePath.Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
	}
	
	if (DownloadPath.Path.IsEmpty())
	{
		DownloadPath.Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());		
	}
	sleeptime = 0.2f;

	bShowServerMesg = true;
	
	Suffix = TEXT(".dep");

	InsProjectName = TEXT("ProjOne");

	WebURL = TEXT("http://192.168.0.186:8080/site/");
}

