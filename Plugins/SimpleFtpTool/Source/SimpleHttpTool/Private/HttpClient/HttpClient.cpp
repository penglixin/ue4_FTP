#include "HttpClient/HttpClient.h"

SimpleHttpRequest::FHttpClient::FHttpClient()
{
}

bool SimpleHttpRequest::FHttpClient::GetObject(FGetObjectRequest& Request) const
{
	return Request.ProcessRequest();
}

bool SimpleHttpRequest::FHttpClient::DeleteObject(FDeleteObjectRequest& Request) const
{
	return Request.ProcessRequest();
}

bool SimpleHttpRequest::FHttpClient::PutObject(FPutObjectRequest& Request) const
{
	return Request.ProcessRequest();
}

bool SimpleHttpRequest::FHttpClient::PostObject(FPostObjectRequest& Request) const
{
	return Request.ProcessRequest();
}

void SimpleHttpRequest::FHttpClient::AbortRequest(IHTTPClientRequest& Request)
{
	Request.CancelRequest();
}
