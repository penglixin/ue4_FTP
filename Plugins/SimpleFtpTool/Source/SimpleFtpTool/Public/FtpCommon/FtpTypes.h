// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EFtpCommandType : uint8
{
	//ABOR the connection
	ABOR = 0,
	//user name
	USER,
	//password
	PASS,
	//return the specific file size
	SIZE,
	//change the work dir
	CWD,
	//zhudongmoshi
	PORT,
	//download file
	RETR,
	//upload file
	STOR,
	//delete specific file
	DELE,
	//list content of specific dir
	NLST,
	//list the file or dictionary
	LIST,		
	//create folder
	MKD,		
	//show current work dir
	PWD,		
	//delete specific dir
	RMD,		
	//set data typr(A=ASCII, E=EBCDIC, I=binary)
	TYPE,		
	//quit
	QUIT		

};

UENUM(BlueprintType)
enum class EFileType : uint8
{
	FOLDER = 0,
	FILE
};


UENUM(BlueprintType)
enum class EFolderType : uint8
{
	MATERIAL = 0,
	TEXTURE,
	ANIMATION,
	STATICMESH,
	SKLETALMESH,
	ERROR_FOLDER
};