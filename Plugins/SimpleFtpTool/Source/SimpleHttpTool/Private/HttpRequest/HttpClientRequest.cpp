#include "HttpRequest/HttpClientRequest.h"

SimpleHttpRequest::FPutObjectRequest::FPutObjectRequest(const FString& URL, const FString& ContentString)
{
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("PUT"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpRequest->SetContentAsString(ContentString);
}

SimpleHttpRequest::FPutObjectRequest::FPutObjectRequest(const FString& URL, const TArray<uint8>& ContentString)
{
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("PUT"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpRequest->SetContent(ContentString);
}

SimpleHttpRequest::FGetObjectRequest::FGetObjectRequest(const FString& URL)
{
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
}

SimpleHttpRequest::FPostObjectRequest::FPostObjectRequest(const FString& URL, const FString& SendMesg)
{
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	HttpRequest->SetContentAsString(SendMesg);
}

SimpleHttpRequest::FDeleteObjectRequest::FDeleteObjectRequest(const FString& URL)
{
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("DELETE"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
}

