// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FtpUMG/FtpWebBrowser.h"
#include "DownloadWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEFTPTOOL_API UDownloadWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(Meta = (BindWidget))
		class UFtpWebBrowser* webBrowser;
	
protected:

	virtual bool Initialize() override;
	
};
