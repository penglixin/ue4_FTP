// Fill out your copyright notice in the Description page of Project Settings.


#include "WebRemoteActor.h"
#include "FtpClient/FtpClient.h"
#include "Editor.h"
#include "FtpUMG/DownloadWidget.h"
#include "Kismet/KismetSystemLibrary.h"


#define LOCTEXT_NAMESPACE "WebRemoteActor"

// Sets default values
AWebRemoteActor::AWebRemoteActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MyPathName = this->GetPathName();

	WebURL = FString("http://192.168.0.186:8080/index.html/#/?objectPath=") + MyPathName;

	
}

// Called when the game starts or when spawned
void AWebRemoteActor::BeginPlay()
{
	Super::BeginPlay();
}

FString AWebRemoteActor::GetMyPathName()
{
	return MyPathName;
}

void AWebRemoteActor::asd(const TArray<FString>& InputVal)
{
	for (const auto& temp : InputVal)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, temp);
		FTP_INSTANCE->FTP_DownloadFiles(temp);
	}
}

void AWebRemoteActor::ShowWeb()
{
	UWorld* EWorld = GEditor->GetEditorWorldContext().World();
	check(EWorld);
	UKismetSystemLibrary::ExecuteConsoleCommand(EWorld, FString("WebControl.StartServer"));		//¿ªÆô¼àÌý
	DownloadUI = CreateWidget<UDownloadWidget>(EWorld, LoadClass<UDownloadWidget>(this, TEXT("WidgetBlueprint'/SimpleFtpTool/WebWidget.WebWidget_C'")));
	DownloadUI->webBrowser->SetInitialURL(WebURL);
	if(DownloadUI)
	{
		TSharedRef<SWindow> WebWindow = SNew(SWindow)
			.Title(LOCTEXT("TesteditorWindows", "Download"))
			.ClientSize(FVector2D(940.f, 540.f))
			.SizingRule(ESizingRule::UserSized)
			.SupportsMinimize(true)
			.SupportsMaximize(true);

		WebWindow->SetContent(DownloadUI->TakeWidget());
		FSlateApplication::Get().AddWindow(WebWindow);
	}
}

#undef LOCTEXT_NAMESPACE
