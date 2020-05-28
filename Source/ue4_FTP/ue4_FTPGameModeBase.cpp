// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "ue4_FTPGameModeBase.h" 
#include "Engine.h"

void Aue4_FTPGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

bool Aue4_FTPGameModeBase::FTP_CreateControlSocket(const FString& ip, int32 port)
{ 
	return FTP_INSTANCE->FTP_CreateControlSocket(ip, port);
}

bool Aue4_FTPGameModeBase::FTP_SendCommand(EFtpCommandType type, FString Param)
{
	return FTP_INSTANCE->FTP_SendCommand(type,Param);
}

bool Aue4_FTPGameModeBase::FTP_DownloadFile(FString ServerFilePath, FString SavePath)
{
	return FTP_INSTANCE->FTP_DownloadOneFile(ServerFilePath, SavePath);
}

bool Aue4_FTPGameModeBase::FTP_DownloadFiles(const FString& serverFolder, const FString& localSavePath)
{
	return FTP_INSTANCE->FTP_DownloadFiles(serverFolder,localSavePath);
}

bool Aue4_FTPGameModeBase::FTP_List(const FString& serverPath, TArray<FString>& OutFiles)
{
	return FTP_INSTANCE->FTP_ListFile(serverPath,OutFiles);
}

bool Aue4_FTPGameModeBase::FTP_UploadFiles(const FString& localPath, TArray<FString>& NotValidFiles, TArray<FString>& DepeNotValidFiles)
{
	return FTP_INSTANCE->FTP_UploadOneFile(localPath);
}

bool Aue4_FTPGameModeBase::TEST_Function(const FString& InFolderPath, FDateTime& DataTime)
{
	return FTP_INSTANCE->ftp_test(InFolderPath, DataTime);
}

bool Aue4_FTPGameModeBase::MoveFile(const FString& to, const FString& from, bool bReplace)
{
	return IFileManager::Get().Move(*to, *from, bReplace);
}

int32 Aue4_FTPGameModeBase::CopyFile(const FString& to, const FString& from, bool bReplace)
{
	return IFileManager::Get().Copy(*to, *from, bReplace);
}

