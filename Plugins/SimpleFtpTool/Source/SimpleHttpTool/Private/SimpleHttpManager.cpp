#include "SimpleHttpManager.h"


HttpManager* HttpManager::httpInstance = nullptr;

HttpManager::HttpManager()
{
}

HttpManager::~HttpManager()
{
}

HttpManager* HttpManager::Get()
{
	if (!httpInstance)
	{
		httpInstance = new HttpManager();
	}
	return httpInstance;
}

void HttpManager::Destroy()
{
	if (httpInstance)
	{
		delete httpInstance;
	}
	httpInstance = nullptr;
}

bool HttpManager::PostIconAndDesc(const FHttpDelegate& HttpDelegates, const FString& URL, const FString& sendMesg)
{
	FHttpSingleRequest* HttpObject = new FHttpSingleRequest();
	HttpObject->SimpleCompleteDelegate = HttpDelegates.SimpleCompleteDelegate;
	HttpObject->SimpleSingleRequestHeaderReceivedDelegate = HttpDelegates.SimpleSingleRequestHeaderReceivedDelegate;
	HttpObject->SimpleSingleRequestProgressDelegate = HttpDelegates.SimpleSingleRequestProgressDelegate;

	return HttpObject->PostIconAndDesc(URL, sendMesg);
}
