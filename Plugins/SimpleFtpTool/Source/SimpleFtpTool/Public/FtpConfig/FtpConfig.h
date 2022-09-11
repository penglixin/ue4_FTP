// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "FtpCommon/FtpTypes.h"
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

	UPROPERTY(config, EditAnywhere, Category = "FtpDescription", meta = (EditCondition = "false", ToolTip = "the web url."))
		FString WebURL;

	UPROPERTY(config, EditAnywhere, Category = "FtpDescription|Instance", meta = (ToolTip = "the InstanceIcon for this submit."))
		FFilePath InstanceIcon;

	UPROPERTY(config, EditAnywhere, Category = "FtpDescription|Instance", meta = (ToolTip = "the description for this submit."))
		FString InstanceDescription;

	UPROPERTY(config, EditAnywhere, Category = "FtpDescription|ThirdParty", meta = (ToolTip = "the ThirdPartyIcon for this submit."))
		TArray<FSubmitThirdPartyInfo> ThirdPartyDescriptions;

	UPROPERTY(config, EditAnywhere, Category = "FtpDescription|Common", meta = (ToolTip = "the CommonIcons for this submit."))
		TArray<FSubmitAssetInfo> CommonDescriptions;
	
	UPROPERTY(config, EditAnyWhere, Category = "FtpDepCachePath", meta = (ToolTip = "the path to save server dep file."))
		FDirectoryPath CachePath;

	UPROPERTY(config, EditAnyWhere, Category = "FtpAssetDownloadPath", meta = (EditCondition  = "false", ToolTip = "the path to save download file."))
		FDirectoryPath DownloadPath;

	UPROPERTY(config, EditAnyWhere, Category = "FtpPluginDownloadPath", meta = (EditCondition = "false", ToolTip = "the path to save download plugins."))
		FDirectoryPath PluginPath;
	
};
