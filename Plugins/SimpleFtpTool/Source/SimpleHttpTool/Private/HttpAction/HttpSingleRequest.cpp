#include "HttpAction/HttpSingleRequest.h"
#include "HttpClient/HttpClient.h"



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
