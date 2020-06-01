// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WebBrowser.h"
#include "FtpWebBrowser.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEFTPTOOL_API UFtpWebBrowser : public UWebBrowser
{
	GENERATED_BODY()

public:

	void SetInitialURL(const FString& InURL);

	
};
