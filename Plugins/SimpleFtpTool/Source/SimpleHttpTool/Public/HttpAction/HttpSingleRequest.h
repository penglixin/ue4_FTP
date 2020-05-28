// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpCommon/SimpleHttpType.h"



struct SIMPLEHTTPTOOL_API FHttpSingleRequest
{

public:

	FSimpleCompleteDelegate SimpleCompleteDelegate;
	FSimpleSingleRequestProgressDelegate SimpleSingleRequestProgressDelegate;
	FSimpleSingleRequestHeaderReceivedDelegate SimpleSingleRequestHeaderReceivedDelegate;

public:
	FHttpSingleRequest();
	virtual ~FHttpSingleRequest();

	bool PostIconAndDesc(const FString& URL, const FString& sendMesg);

protected:
	
	virtual void HttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectSuccessfully);
	virtual void HttpRequestProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesRecv);
	virtual void HttpRequestHeaderReceived(FHttpRequestPtr Request, const FString& HeaderName, const FString& NewHeaderValue);



};