// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FtpClient/FtpClient.h"
#include "ue4_FTPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4_FTP_API Aue4_FTPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable,Category = "FTP")
		bool FTP_CreateControlSocket(const FString& ip, int32 port);

	UFUNCTION(BlueprintCallable, Category = "FTP")
		bool FTP_RecvData(FString& RecvMesg, bool bSleep = true);

	UFUNCTION(BlueprintCallable, Category = "FTP")
		bool FTP_SendCommand(EFtpCommandType type, FString Param);

	UFUNCTION(BlueprintCallable, Category = "FTP")
		bool FTP_CreateDataSocket_PASV(int32 port);

	UFUNCTION(BlueprintCallable, Category = "FTP")
		bool test();

};
