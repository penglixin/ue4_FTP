// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "FtpConfig.generated.h"


//struct FSlateBrush;

/**
 * 
 */
UCLASS(config = UFtpConfig)
class SIMPLEFTPTOOL_API UFtpConfig : public UObject
{
	GENERATED_BODY()

public:

	UFtpConfig();

	UPROPERTY(config, EditAnywhere, Category = "FtpDebug", meta = (ToolTip = "show the debug message."))
		bool bShowServerMesg;

	UPROPERTY(config, EditAnywhere, Category = "FtpDebug", meta = (ClampMin =0.2f, ClampMax = 2.f, ToolTip = "sleep time."))
		float sleeptime;

	UPROPERTY(config, EditAnywhere, Category = "FtpSettings", meta = (ToolTip = "Set a Suffix for dependent file (include dot)."))
		FString Suffix;

	UPROPERTY(config, EditAnywhere, Category = "FtpInstProjectName", meta = (ToolTip = "the name of instance."))
		FString InsProjectName;

	//UPROPERTY(config, EditAnywhere, Category = "FtpSubmitDescription", meta = (ToolTip = "the icon for this submit."))
	//	FSlateBrush Icon;

	UPROPERTY(config, EditAnywhere, Category = "FtpSubmitDescription", meta = (ToolTip = "the description for this submit."))
		FString SubmitDescription;
	
	UPROPERTY(config, EditAnyWhere, Category = "FtpDepCachePath", meta = (ToolTip = "the path to save server dep file."))
		FDirectoryPath CachePath;

	UPROPERTY(config, EditAnyWhere, Category = "FtpAssetDownloadPath", meta = (ToolTip = "the path to save server dep file."))
		FDirectoryPath DownloadPath;
};
