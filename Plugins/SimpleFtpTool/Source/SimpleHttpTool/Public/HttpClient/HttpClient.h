// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpRequest/HttpClientRequest.h"

using namespace SimpleHttpRequest;

namespace SimpleHttpRequest
{
	struct SIMPLEHTTPTOOL_API FHttpClient
	{
		FHttpClient();

		bool GetObject(FGetObjectRequest& Request) const;
		bool DeleteObject(FDeleteObjectRequest& Request) const;
		bool PutObject(FPutObjectRequest& Request) const;
		bool PostObject(FPostObjectRequest& Request) const;
		void AbortRequest(IHTTPClientRequest& Request);
	};
}