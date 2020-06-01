// Fill out your copyright notice in the Description page of Project Settings.


#include "FtpUMG/DownloadWidget.h"


bool UDownloadWidget::Initialize()
{
	if(!Super::Initialize())
		return false;
	
	//webBrowser->SetInitialURL(FString("http://192.168.0.186:8080/index.html/#/?objectPath=/Game/ThirdPersonBP/Maps/ThirdPersonExampleMap.ThirdPersonExampleMap:PersistentLevel.testremote_1"));
	return true;
}

