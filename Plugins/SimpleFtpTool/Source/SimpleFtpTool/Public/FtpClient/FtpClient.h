// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Networking.h"
#include "FtpConfig/FtpConfig.h"
#include "FtpClient/FtpTypes.h" 
#include "FtpClient/FtpMacro.h"



class SIMPLEFTPTOOL_API FtpClientManager
{

public:
	FtpClientManager();
	~FtpClientManager();
	static FtpClientManager* Get();
	static void Destroy();

private:
	//控制连接 :一直保持连接直到程序结束
	FSocket* controlSocket;
	//数据连接： 在发送文件操作请求（上传下载）时建立连接，完成操作后断开连接
	FSocket* dataSocket;
	FIPv4Address ipAddr;

public:
	
	/*********************************************************************/
	/*************************ftp客户端操作接口****************************/
	/*********************************************************************/
	//创建controlsocket
	bool FTP_CreateControlSocket(FString IP = TEXT("192.168.0.4"), int32 port = 21);
	//接受服务端返回的消息
	bool FTP_ReceiveData(FString& RecvMesg, bool bSleep = true);
	//发送指令
	bool FTP_SendCommand(const EFtpCommandType& cmdtype, const FString& Param);
	
	//创建 dataSocket
	bool FTP_CreateDataSocket_PASV(int32 port2);
	
	
	//需要用到数据连接的命令：NLST,LIST,RETR,STOR
	bool FTP_StorFile(const FString& servetPath, const FString& localFilePath);

private:
	//将接收到的数据转换成FString
	FString BinaryArrayToString(TArray<uint8> BinaryArray);
	//转换指令
	FString SwitchCommand(const EFtpCommandType& cmdtype, const FString& Param);
	//从服务器返回的字符串中获取新的端口号
	int32 GetPASVPortFromString(const FString& RecvMesg);
	//发送PASV命令，获取服务器返回的端口号  单独把这条命令拿出来是为了方便获取服务器返回的端口
	int32 FTP_SendPASVCommand();
private:

	static FtpClientManager* ftpInstance;
	
};

#define FTP_INSTANCE FtpClientManager::Get()
