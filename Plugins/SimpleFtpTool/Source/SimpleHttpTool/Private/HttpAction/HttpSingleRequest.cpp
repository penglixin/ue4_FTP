#include "HttpAction/HttpSingleRequest.h"
#include "HttpClient/HttpClient.h"

#if WITH_EDITOR
#if PLATFORM_WINDOWS
#pragma optimize("",off)
#endif
#endif

FHttpSingleRequest::FHttpSingleRequest()
{
}

FHttpSingleRequest::~FHttpSingleRequest()
{
}

bool FHttpSingleRequest::PostIconAndDesc(const FString& URL, const FString& sendMesg)
{
	FHttpClient client;
	FPostObjectRequest Request(URL, sendMesg);
	Request << FHttpRequestHeaderReceivedDelegate::CreateRaw(this, &FHttpSingleRequest::HttpRequestHeaderReceived)
			<< FHttpRequestProgressDelegate::CreateRaw(this, &FHttpSingleRequest::HttpRequestProgress)
			<< FHttpRequestCompleteDelegate::CreateRaw(this, &FHttpSingleRequest::HttpRequestComplete);
	return client.PostObject(Request);
}

void FHttpSingleRequest::HttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectSuccessfully)
{
	FString Verb = Request->GetVerb();
	FString URL = Request->GetURL();
	uint8 Status = (uint8)Request->GetStatus();
	float ElapsedTime = Request->GetElapsedTime();
	FString ContentType = Request->GetContentType();
	int32 ContentLength = Request->GetContentLength();


	int32 responceCode = Response->GetResponseCode();
	FString ResponseURL = Response->GetURL();
	FString ResponseContentType = Response->GetContentType();
	int32 ResponseContentLength = Response->GetContentLength();
	FString ResponseMessage = Response->GetContentAsString();
	TArray<uint8> ResponseContent = Response->GetContent();

	bool bRequest = Request.IsValid();
	bool bResponse = Response.IsValid();

	if (Request.IsValid() && Response.IsValid() && bConnectSuccessfully && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		SimpleCompleteDelegate.ExecuteIfBound(Request, Response, bConnectSuccessfully);
	}
	delete this;
}

void FHttpSingleRequest::HttpRequestProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesRecv)
{
	SimpleSingleRequestProgressDelegate.ExecuteIfBound(Request, BytesSent, BytesRecv);
}

void FHttpSingleRequest::HttpRequestHeaderReceived(FHttpRequestPtr Request, const FString& HeaderName, const FString& NewHeaderValue)
{
	SimpleSingleRequestHeaderReceivedDelegate.ExecuteIfBound(Request, HeaderName, NewHeaderValue);
}


#if WITH_EDITOR
#if PLATFORM_WINDOWS
#pragma optimize("",on)
#endif
#endif