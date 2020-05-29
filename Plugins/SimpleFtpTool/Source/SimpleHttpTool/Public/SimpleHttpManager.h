// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "HttpCommon/SimpleHttpType.h"
#include "HttpAction/HttpSingleRequest.h"

class SIMPLEHTTPTOOL_API HttpManager
{

public:
	HttpManager();
	~HttpManager();
	static HttpManager* Get();
	static void Destroy();

public:
	
	bool PostIconAndDesc(const FHttpDelegate& HttpDelegates, const FString& URL, const FString& sendMesg);
	bool PostIconAndDesc(const FString& URL, const FString& sendMesg);

private:
	static HttpManager* httpInstance;

};

#define HTTP_INSTANCE HttpManager::Get()