#include "FtpClient/FtpClient.h"
#include "Engine.h"


#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif


void Print(const FString& Mesg, float Time = 100.f, FColor Color = FColor::Yellow)
{
	if (GEngine && GetDefault<UFtpConfig>()->bShowDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, Color, Mesg);
	}
}

FtpClientManager* FtpClientManager::ftpInstance = nullptr;

FtpClientManager::FtpClientManager()
{ 
}

FtpClientManager::~FtpClientManager()
{
	if (controlSocket)
	{
		controlSocket->Close();
		controlSocket = nullptr;
	}
	if (dataSocket)
	{
		dataSocket->Close();
		dataSocket = nullptr;
	}
}

FtpClientManager* FtpClientManager::Get()
{
	if (!ftpInstance)
	{
		ftpInstance = new FtpClientManager();
	}
	return ftpInstance;
}

void FtpClientManager::Destroy()
{
	if (ftpInstance)
	{
		delete ftpInstance;
	}
	ftpInstance = nullptr;
}

FString FtpClientManager::BinaryArrayToString(TArray<uint8> BinaryArray)
{
	return FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(BinaryArray.GetData())));
}

FString FtpClientManager::SwitchCommand(const EFtpCommandType& cmdtype, const FString& Param)
{
	FString cmd;

	switch (cmdtype)
	{
		//中断数据连接
		case EFtpCommandType::ABOR:
			cmd = TEXT("ABOR ");
			cmd.Append(TEXT("\r\n"));
			break;
		//指定用户名
		case EFtpCommandType::USER:
			cmd = TEXT("USER ") + Param;
			cmd.Append(TEXT("\r\n"));
			break;
		//登录密码
		case EFtpCommandType::PASS:
			cmd = TEXT("PASS ") + Param;
			cmd.Append(TEXT("\r\n"));
			break;
		//从服务器上返回指定文件的大小
		case EFtpCommandType::SIZE:
			cmd = TEXT("SIZE ") + Param;
			cmd.Append(TEXT("\r\n"));
			break;
		//改变工作目录
		case EFtpCommandType::CWD:
			cmd = TEXT("CWD ") + Param;
			cmd.Append(TEXT("\r\n"));
			break;
		//告诉 FTP 服务器客户端监听的端口号，让 FTP 服务器采用主动模式连接客户端
		case EFtpCommandType::PORT:
			cmd = TEXT("PORT ") + Param;
			cmd.Append(TEXT("\r\n"));
			break;
		//下载文件
		case EFtpCommandType::RETR:
			cmd = TEXT("RETR ") + Param;
			cmd.Append(TEXT("\r\n"));
			break;
		//上传文件
		case EFtpCommandType::STOR: 
			cmd = TEXT("STOR ") + Param;
			cmd.Append(TEXT("\r\n"));
			break;
		//删除服务器上的指定文件
		case EFtpCommandType::DELE:
			cmd = TEXT("DELE ") + Param;
			cmd.Append(TEXT("\r\n"));
			break;
		//列出指定目录下的内容
		case EFtpCommandType::NLST:
			cmd = TEXT("NLST ") + Param;
			cmd.Append(TEXT("\r\n"));
			break;
		//如果是文件名列出文件信息，如果是目录则列出文件列表
		case EFtpCommandType::LIST:
			cmd = TEXT("LIST ") + Param;
			cmd.Append(TEXT("\r\n"));
			break;
		//在服务器上建立指定目录
		case EFtpCommandType::MKD:
			cmd = TEXT("MKD ") + Param;
			cmd.Append(TEXT("\r\n"));
			break;
		//显示当前工作目录
		case EFtpCommandType::PWD:
			cmd = TEXT("PWD ");
			cmd.Append(TEXT("\r\n"));
			break;
		//在服务器删除指定目录
		case EFtpCommandType::RMD:
			cmd = TEXT("RMD ") + Param;
			cmd.Append(TEXT("\r\n"));
			break;
		//设置数据类型（A=ASCII，E=EBCDIC，I=binary）
		case EFtpCommandType::TYPE:
			cmd = TEXT("TYPE ") + Param;
			cmd.Append(TEXT("\r\n"));
			break;
		//退出登录
		case EFtpCommandType::QUIT:
			cmd = TEXT("QUIT ");
			cmd.Append(TEXT("\r\n"));
			break;
		default:
			break;
	}
	return cmd;
}

int32 FtpClientManager::GetPASVPortFromString(const FString& RecvMesg)
{
	auto lambda = [](const FString& split, FString R_String, bool bRight)->FString
	{
		FString L, R;
		R_String.Split(split, &L, &R);
		if (bRight)
			return R;
		else
			return L;
	};
	int32 p1 = 0, p2 = 0;
	//227 Entering Passive Mode (192,168,0,4,255,245)
	//先判断响应码是不是等于227
	FString LeftString = lambda(TEXT(" "), RecvMesg, false);
	int32 ResponseCode = FCString::Atoi(*LeftString);
	if (PASV_MODE != ResponseCode)
	{
		return -1;
	}
	FString RightString =lambda(TEXT("("), RecvMesg, true);
	for (int32 i = 0; i < 5; i++)
	{
		RightString = lambda(TEXT(","), RightString, true);
		if (3 == i)
		{
			p1 = FCString::Atoi(*RightString);
		}
		if (4 == i)
		{
			p2 = FCString::Atoi(*RightString);
		}
	}
	return (p1 * 256 + p2);
}

bool FtpClientManager::FTP_CreateControlSocket( FString IP,  int32 port)
{ 
	//转换Ip地址
	FIPv4Address::Parse(IP, ipAddr);
	//创建一个 FInternetAddr 存放IP和端口
	TSharedPtr<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ipAddr.Value);
	addr->SetPort(port);
	//创建controlSocket
	controlSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	//连接服务器
	if (controlSocket->Connect(*addr))
	{
		FString RecvMesg;
		TArray<uint8> RecvBinary;
		FTP_ReceiveData(RecvMesg);
		return true;
	}
	Print("controlSocket connect failed!");
	return false; 
}

bool FtpClientManager::FTP_ReceiveData(FString& RecvMesg , bool bSleep)
{
	if(bSleep)
		FPlatformProcess::Sleep(1.f);
	if (!controlSocket)
	{
		RecvMesg = TEXT("Error:control socket is nullptr.");
		Print(RecvMesg);
		return false;
	}
	TArray<uint8> RecvData;
	uint32 size;
	uint8 element = 0;
	while (controlSocket->HasPendingData(size))
	{
		RecvData.Init(element, FMath::Min(size, 65507u));
		int32 read = 0;
		controlSocket->Recv(RecvData.GetData(), RecvData.Num(), read);
	}
	if (RecvData.Num() <= 0)
	{
		RecvMesg = TEXT("Error:RecvData is empty.");
		Print(RecvMesg);
		return false;
	}
	const FString ReceivedUE4String = BinaryArrayToString(RecvData);
	RecvMesg = ReceivedUE4String;
	Print(RecvMesg);
	return true;
}

bool FtpClientManager::FTP_SendCommand(const EFtpCommandType& cmdtype, const FString& Param)
{
	FString strCommand = SwitchCommand(cmdtype, Param);
	TCHAR* serializedChar = strCommand.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar) + 1;
	int32 sent = 0;
	if (controlSocket->Send((uint8*)TCHAR_TO_UTF8(serializedChar),size,sent))
	{
		Print("SendCommand  " + Param + "  succeed!");
		FString RecvMesg;
		FTP_ReceiveData(RecvMesg);
		return true;
	}
	Print("SendCommand " + Param + " failed!");
	return false;
}

int32 FtpClientManager::FTP_SendPASVCommand()
{
	FString cmd_PASV = TEXT("PASV \r\n");
	TCHAR* serializedChar = cmd_PASV.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar) + 1;
	int32 sent = 0;
	if (controlSocket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent))
	{
		Print("set pasv mode.");
		FString RecvMesg;
		FTP_ReceiveData(RecvMesg);
		return GetPASVPortFromString(RecvMesg);
	}
	return -1;
}

bool FtpClientManager::FTP_CreateDataSocket_PASV(int32 port2)
{
	//这里采用被动模式（PASV），发送PASV命令服务器会返回一串数字<,h2,h3,h4,p1,p2>并且打开一个新端口供客户端dataSocket连接 h1.h2.h3.h4 代表服务器IP地址，新端口port = p1*256+p2
	//创建一个FInternetAddr，存放IP和端口
	TSharedPtr<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ipAddr.Value);
	addr->SetPort(port2);
	//创建dataSocket
	dataSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	if (dataSocket->Connect(*addr))
	{
		return true;
	}
	Print("dataSocket connect failed!");
	if (dataSocket)
	{
		delete dataSocket;
		dataSocket = nullptr;
	}
	return false;
}

bool FtpClientManager::FTP_StorFile(const FString& servetPath, const FString& localFilePath)
{
	//先发送PASV指令
	int32 PasvPort = FTP_SendPASVCommand();
	//创建数据连接
	FTP_CreateDataSocket_PASV(PasvPort);
	//传输文件操作...


	return false;
}

#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif