// Fill out your copyright notice in the Description page of Project Settings.


#include "WebRemoteActor.h"
#include "FtpClient/FtpClient.h"
#include "Editor.h"
#include "UObject/ConstructorHelpers.h"

#define LOCTEXT_NAMESPACE "WebRemote"

// Sets default values
AWebRemoteActor::AWebRemoteActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MyPathName = this->GetPathName();
	static ConstructorHelpers::FClassFinder<UUserWidget>widget(TEXT("WidgetBlueprint'/SimpleFtpTool/DownloadUI.DownloadUI'_C"));
	if(widget.Succeeded())
	{
		//TestUI = widget.Class;
	}
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

void AWebRemoteActor::Download(const TArray<FString>& InputVal)
{
	for (const auto& temp : InputVal)
	{
		FTP_INSTANCE->FTP_DownloadFiles(temp);
	}
}

void AWebRemoteActor::asd(const FString& InputVal)
{
	GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Purple,InputVal);
	UWorld* EWorld = GEditor->GetEditorWorldContext().World();
	check(EWorld);
	UUserWidget* TestUIs = CreateWidget<UUserWidget>(EWorld, TestUI);
	if(TestUI)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Purple, TestUI->GetName());

		TSharedRef<SWindow> TestWindows = SNew(SWindow)
			.Title(LOCTEXT("TesteditorWindows", "Download"))
			.ClientSize(FVector2D(940.f, 540.f))
			.SizingRule(ESizingRule::UserSized)
			.SupportsMinimize(true)
			.SupportsMaximize(true);

		TestWindows->SetContent(TestUIs->TakeWidget());
		FSlateApplication::Get().AddWindow(TestWindows);

	}
}

#undef LOCTEXT_NAMESPACE