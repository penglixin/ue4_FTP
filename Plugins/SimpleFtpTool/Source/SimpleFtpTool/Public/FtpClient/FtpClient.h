// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Networking.h"
#include "FtpConfig/FtpConfig.h"
#include "FtpCommon/FtpTypes.h" 
#include "FtpCommon/FtpMacro.h"
#include "SimpleHttpManager.h"


class SIMPLEFTPTOOL_API FtpClientManager
{

public:
	FtpClientManager();
	~FtpClientManager();
	static FtpClientManager* Get();
	static void Destroy();
	//初始化文件目录结构
	void Initialize_Folder();
	//创建实例文件夹
	void CreateInstanceFolder(const FString& InstanceName);
	void ShowMessageBox(const TArray<FString>& NameNotValidFiles, const TArray<FInvalidDepInfo>& DepenNotValidFiles);

	//上传图片以及说明到web服务器
	//1. 实例上传
	//2. 单个资源上传
	//3. 第三方文件加上传
	bool UploadInstanceDescriptToWeb(const FString& InFolderPath, const TArray<FString>& ThirdFolders, const TArray<FString>& InPluginPath);

	bool UploadAssetsDescriptToWeb(const TArray<FString>& InAssetPaths);

	bool UploadThirdFolderDescriptToWeb(const TArray<FString>& InThirdPath);

	bool UploadPluginDescriptToWeb(const TArray<FString>& InPluginPath);
	
public:
	/*********************************************************************/
	/*************************ftp客户端操作接口****************************/
	/*********************************************************************/
	//创建controlsocket
	bool FTP_CreateControlSocket(const FString& IP, const int32& port);
	//发送指令
	bool FTP_SendCommand(const EFtpCommandType& cmdtype, const FString& Param);
	//需要用到数据连接的命令：NLST,LIST,RETR,STOR
	//列举文件夹 (相对路径)
	bool FTP_ListFile(const FString& serverPath, TArray<FString>& OutFiles, bool bIncludeFolder = true);
	//下载单个文件 规定文件路径用/隔开 如：/Folder1/Folder2/adadd.txt localpath:需要用绝对路径如：E:/Game/Folder
	bool FTP_DownloadOneFile(const FString& serverFileName, FString Savepath = GetDefault<UFtpConfig>()->DownloadPath.Path);
	//下载文件夹里的所有文件 serverFolder:如 /asd				localpath:需要用绝对路径如：E:/Game/Folder
	bool FTP_DownloadFiles(const FString& serverFolder, FString Savepath = GetDefault<UFtpConfig>()->DownloadPath.Path);
	//上传单个文件
	bool FTP_UploadOneFile(const FString& localFileName, bool bIsPlugin = false);
	//上传文件夹里的所有文件
	bool FTP_UploadFilesByFolder(const FString& InGamePath, TArray<FString>& NameNotValidFiles, TArray<FInvalidDepInfo>& DepenNotValidFiles);
	//根据PackageName上传资源
	bool FTP_UploadFilesByAsset(const TArray<FString>& InPackNames, TArray<FString>& NameNotValidFiles, TArray<FInvalidDepInfo>& DepenNotValidFiles);

	bool ftp_test(const FString& InFolderPath, const FString& URL);

public:
	//列举路径下的所有文件(绝对路径)
	bool GetAllFileFromLocalPath(const FString& localPath, TArray<FString>& AllFiles, bool bRecursively = true);
	//创建文件夹
	bool CreateDirByAsssetPath(const FString& InAssetFullPath);
	//删除文件夹里面所有内容
	bool DeleteFileOrFolder(const FString& InDir);
	//检测单个文件夹下的文件命名是否合法(只能是../../Common_Material  或者 ../../Ins_Material 文件夹，如果是其他文件夹例如 ../../Instance/ProjA 需要将他的子文件夹列出来，然后每个子文件夹都执行一次这个方法)
	bool FileNameValidationOfOneFolder(TArray<FString>& NoValidFiles, const FString& InFullFolderPath);
	//寻找一个资源的所有依赖
	void RecursiveFindDependence(const FString& InPackageName, TArray<FString>& AllDependence);
	//检查一个资源的所有依赖是否合法
	bool ValidationDependenceOfOneAsset(const FString& InGamePath, const FString& AssetPackName, const TArray<FString>& TheAssetDependence, FInvalidDepInfo& InvalidInfo, bool& bDepHasChanged, bool bAllNameValid);
	//检查一个文件夹下的所有资源的所有依赖
	bool ValidationAllDependenceOfTheFolder(const FString& InGamePath, TArray<FInvalidDepInfo>& NotValidDependences, bool bAllNameValid = false);
	//上传文件以及依赖文件 传入资源的PackageName数组
	bool UploadDepenceAssetAndDepences(const TArray<FString>& InPackageNames);
	//判断是插件还是普通资源（发送SIZE 命令，根据服务器返回的响应码判断文件是否存在，然后再根据用户做出的选择是否覆盖服务器文件，这一步并没有使用到校验码）
	bool IsPlugin(const FString& ServerFileName);
	//校验资源校验码
	bool IsAssetValidCodeSame(const FString& InPakName);
	//校验实例校验码
	bool IsInstValidCodeSame(const FString& InstName);
	//检查实例是否依赖第三方资源 传入实例文件夹路径
	void HasDepencyThirdAsset(const FString& InGamePath, TArray<FString>& ThirdPartyName, TArray<FString>& PluginName);
	//提交第三方文件夹
	void UploadThirdPartyFolder(const TArray<FString>& InFolders);
	//提交第三方文件夹
	void UploadPluginFolder(const TArray<FString>& InFolders);
	//下载实例的依赖文件（公共资源和依赖资源）
	bool DownloadDepenceAsset(const FString& InInstFolderPath);
	
private:
	//获取本地IP
	FString GetMylocalIPADDR();
	//接受服务端返回的消息
	bool ReceiveData(FSocket* sock, FString& RecvMesg, TArray<uint8>& dataArray, bool bSleep = true);
	//创建 dataSocket
	bool CreateDataSocket_PASV(int32 port2);
	//将接收到的二进制数据转换成FString
	FString BinaryArrayToString(const TArray<uint8>& BinaryArray);
	//转换指令
	FString SwitchCommand(const EFtpCommandType& cmdtype, const FString& Param);
	//从服务器返回的字符串中获取新的端口号
	int32 GetPASVPortFromString(const FString& RecvMesg);
	//发送PASV命令，获取服务器返回的端口号  单独把这条命令拿出来是为了方便获取服务器返回的端口
	int32 SendPASVCommand();
	//判断传入的serverPath是文件 还是 文件夹
	EFileType JudgeserverPath(const FString& InserverPath);
	
private:
	//Debug
	void Print(const FString& Mesg, float Time = 100.f, FColor Color = FColor::Yellow);
	void Print(const TArray<uint8>& dataArray, float Time = 100.f, FColor Color = FColor::Purple);
	//删除没有用到的依赖文件
	void DeleteUselessFile();

private:
	static FtpClientManager* ftpInstance;
	int32 ResponseCode;			//服务器响应码
	FSocket* controlSocket;		//控制连接 :一直保持连接直到程序结束，或者服务器关闭
	FSocket* dataSocket;		//数据连接 :在发送文件操作请求（上传下载）时建立连接，完成操作后断开连接
	FIPv4Address ipAddr;
	
	//上传第三方资源包
	FUploadThirdPartyDelegate UploadThirdPartyDelegate;
	//上传第三方插件
	FUploadThirdPartyDelegate UploadPluginsDelegate;

private:
	FString DataTypeIni;
	
};

#define FTP_INSTANCE FtpClientManager::Get()