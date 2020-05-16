// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "ue4_FTPGameModeBase.h" 

void Aue4_FTPGameModeBase::BeginPlay()
{	
	Super::BeginPlay();
	
}

bool Aue4_FTPGameModeBase::FTP_CreateControlSocket(const FString& ip, int32 port)
{ 
	return FTP_INSTANCE->FTP_CreateControlSocket(ip, port);
}

bool Aue4_FTPGameModeBase::FTP_RecvData(FString& RecvMesg, bool bSleep)
{
	return FTP_INSTANCE->FTP_ReceiveData(RecvMesg, bSleep);
}

bool Aue4_FTPGameModeBase::FTP_SendCommand(EFtpCommandType type, FString Param)
{
	return FTP_INSTANCE->FTP_SendCommand(type,Param);
}

bool Aue4_FTPGameModeBase::FTP_CreateDataSocket_PASV(int32 port)
{
	return FTP_INSTANCE->FTP_CreateDataSocket_PASV(port);
}

bool Aue4_FTPGameModeBase::test()
{
	FString k, l;
	return FTP_INSTANCE->FTP_StorFile(k,l);
}

