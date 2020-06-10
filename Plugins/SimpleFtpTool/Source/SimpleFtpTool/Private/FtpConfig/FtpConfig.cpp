// Fill out your copyright notice in the Description page of Project Settings.

#include "FtpConfig/FtpConfig.h"
#include "Misc/Paths.h"


UFtpConfig::UFtpConfig()
{
	CachePath.Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
	
	DownloadPath.Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());

	PluginPath.Path = FPaths::ConvertRelativePathToFull(FPaths::EngineDir()) + TEXT("Plugins/Marketplace/");

	sleeptime = 0.2f;

	bShowServerMesg = true;
	
	Suffix = TEXT(".dep");

	InsProjectName = TEXT("ProjOne");

	WebURL = TEXT("http://192.168.0.186:8080/site/");
}

