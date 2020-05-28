#include "HttpRequest/RequestInterface.h"
#include "HttpModule.h"


SimpleHttpRequest::IHTTPClientRequest::IHTTPClientRequest()
	:HttpRequest(FHttpModule::Get().CreateRequest())
{
}

bool SimpleHttpRequest::IHTTPClientRequest::ProcessRequest()
{
	return HttpRequest->ProcessRequest();
}

void SimpleHttpRequest::IHTTPClientRequest::CancelRequest()
{
	HttpRequest->CancelRequest();
}
