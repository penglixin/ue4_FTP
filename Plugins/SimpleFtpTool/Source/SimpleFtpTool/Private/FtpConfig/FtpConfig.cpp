// Fill out your copyright notice in the Description page of Project Settings.


#include "FtpConfig/FtpConfig.h"


UFtpConfig::UFtpConfig()
{
	bShowServerMesg = true;

	ServerIP = TEXT("192.168.0.4");

	ServerPort = 21;

	InsProjectName = TEXT("ProjOne");
}

