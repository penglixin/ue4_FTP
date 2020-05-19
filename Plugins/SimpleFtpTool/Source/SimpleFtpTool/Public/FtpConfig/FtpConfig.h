// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FtpConfig.generated.h"

/**
 * 
 */
UCLASS(config = UFtpConfig)
class SIMPLEFTPTOOL_API UFtpConfig : public UObject
{
	GENERATED_BODY()

public:

	UFtpConfig();

	UPROPERTY(config, EditAnywhere, Category = "Debug", meta = (ToolTip = "show the debug message."))
		bool bShowServerMesg;

	UPROPERTY(config, EditAnywhere, Category = "Debug", meta = (ClampMin =0.2f, ClampMax = 2.f, ToolTip = "sleep time."))
		float sleeptime;

	UPROPERTY(config, EditAnywhere, Category = "FtpSettings", meta = (ToolTip = "the ip of FTP Server."))
		FString ServerIP;

	UPROPERTY(config, EditAnywhere, Category = "FtpSettings", meta = (ToolTip = "the port of FTP Server."))
		int32 ServerPort;
	
};
