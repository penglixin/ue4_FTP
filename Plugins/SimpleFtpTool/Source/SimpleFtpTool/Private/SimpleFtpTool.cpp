// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SimpleFtpTool.h"
#include "SimpleFtpToolStyle.h"
#include "SimpleFtpToolCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ISettingsModule.h"
#include "ContentBrowserModule.h"
#include "FtpClient/FtpClient.h"
#include "Misc/MessageDialog.h"

static const FName SimpleFtpToolTabName("SimpleFtpTool");

#define LOCTEXT_NAMESPACE "FSimpleFtpToolModule"

void FSimpleFtpToolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FTP_INSTANCE->Initialize_Folder();
	CreateToFTPServer();
	FSimpleFtpToolStyle::Initialize();
	FSimpleFtpToolStyle::ReloadTextures();
	FSimpleFtpToolCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSimpleFtpToolCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FSimpleFtpToolModule::PluginButtonClicked),
		FCanExecuteAction());

	if (ISettingsModule * SettingModule = FModuleManager::GetModulePtr<ISettingsModule>(TEXT("Settings")))
	{
		SettingModule->RegisterSettings(
			"Project",
			"FTPSetting",
			"MyFTPSetting",
			LOCTEXT("MyFTPSetting", "My FTP Settings"),
			LOCTEXT("MyFTPSettingTips", "select the FTP Server you want to connect."),
			GetMutableDefault<UFtpConfig>());
	}
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FSimpleFtpToolModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FSimpleFtpToolModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SimpleFtpToolTabName, FOnSpawnTab::CreateRaw(this, &FSimpleFtpToolModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FSimpleFtpToolTabTitle", "SimpleFtpTool"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	
	//自定义菜单
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
		TArray<FContentBrowserMenuExtender_SelectedPaths>& ContentBrowserMenuExtender_SelectedPaths = ContentBrowserModule.GetAllPathViewContextMenuExtenders();
		ContentBrowserMenuExtender_SelectedPaths.Add(FContentBrowserMenuExtender_SelectedPaths::CreateRaw(this, &FSimpleFtpToolModule::OnExtendContentBrowser));

		TArray<FContentBrowserMenuExtender_SelectedAssets>& ContentBrowserMenuExtender_SelectedAssets = ContentBrowserModule.GetAllAssetViewContextMenuExtenders();
		ContentBrowserMenuExtender_SelectedAssets.Add(FContentBrowserMenuExtender_SelectedAssets::CreateRaw(this, &FSimpleFtpToolModule::OnExtendContentAssetBrowser));

	}
}

void FSimpleFtpToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSimpleFtpToolStyle::Shutdown();

	FSimpleFtpToolCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SimpleFtpToolTabName);

	FtpClientManager::Destroy();

}

TSharedRef<SDockTab> FSimpleFtpToolModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FSimpleFtpToolModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("SimpleFtpTool.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

TSharedRef<FExtender> FSimpleFtpToolModule::OnExtendContentBrowser(const TArray<FString>& NewPaths)
{
	TSharedRef<FExtender> Extender(new FExtender);

	Extender->AddMenuExtension("FolderContext", EExtensionHook::Before, nullptr, FMenuExtensionDelegate::CreateRaw(this, &FSimpleFtpToolModule::CreateSubMenuForContentBrowser, NewPaths));

	return Extender;
}

void FSimpleFtpToolModule::CreateSubMenuForContentBrowser(FMenuBuilder& MenuBuilder, TArray<FString> NewPaths)
{
	bool bCanSubmit = true;
	for (const auto& Temp : NewPaths)
	{
		if (Temp.Equals("/Game") || Temp.Equals("/Game/Map") || Temp.Equals("/Game/Instance") || Temp.Contains("/Ins_"))   //只能提交实例文件夹，以及公共文件夹
		{
			bCanSubmit = false;
			break;
		}
	}
	MenuBuilder.BeginSection("Custom Menu", LOCTEXT("CustomMenu", "Custom Menu Option"));
	{
		if (bCanSubmit)
		{
			MenuBuilder.AddMenuEntry(
				LOCTEXT("Submit", "Submit Sources"),
				LOCTEXT("SubmitTips", "Submit your source."),
				FSlateIcon(),
				FUIAction(FExecuteAction::CreateRaw(this, &FSimpleFtpToolModule::SubmitSourceUnderTheFolder, NewPaths)));

			MenuBuilder.AddMenuEntry(
				LOCTEXT("GenerateDepend", "Check Name And Dependency"),
				LOCTEXT("GenerateDependTips", "Check Asset Name And Generate Dependency File Under The Folder."),
				FSlateIcon(),
				FUIAction(FExecuteAction::CreateRaw(this, &FSimpleFtpToolModule::CheckNameAndGenerateDependencyFiles, NewPaths)));
		}
		MenuBuilder.AddMenuEntry(
			LOCTEXT("CreateInstance", "Create Inst Folder"),
			LOCTEXT("CreateInstanceTips", "create an instance folder."),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateRaw(this, &FSimpleFtpToolModule::CreateInstanceFolder, NewPaths)));
	}MenuBuilder.EndSection();
}

TSharedRef<FExtender> FSimpleFtpToolModule::OnExtendContentAssetBrowser(const TArray<FAssetData>& NewAssetPaths)
{
	TArray<FString> NewPaths;
	TSharedRef<FExtender> Extender(new FExtender);
	for (const auto& Temp : NewAssetPaths)
	{
		if (Temp.AssetClass != "World")
		{
			NewPaths.Add(Temp.PackageName.ToString());
		}
		else
		{
			return Extender;
		}
	}
	Extender->AddMenuExtension("AssetContextReferences", EExtensionHook::After, nullptr, FMenuExtensionDelegate::CreateRaw(this, &FSimpleFtpToolModule::CreateSubMenuForAssetBrowser, NewPaths));
	return Extender;
}

void FSimpleFtpToolModule::CreateSubMenuForAssetBrowser(FMenuBuilder& MenuBuilder, TArray<FString> NewPaths)
{
	bool bCanSubmit = true;
	for (const auto& temp : NewPaths)
	{
		if (temp.Contains(TEXT("/Ins_")))  //只能提交公共文件夹下的Asset
		{
			bCanSubmit = false;
			break;
		}
	}
	if (!bCanSubmit)
		return;
	MenuBuilder.BeginSection("Custom Menu", LOCTEXT("CustomMenu", "Custom Menu Option"));
	{
		MenuBuilder.AddMenuEntry(
			LOCTEXT("Submit", "Submit Asset"),
			LOCTEXT("SubmitTips", "Submit your assets."),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateRaw(this, &FSimpleFtpToolModule::SubmitSelectedSource, NewPaths)));
	}MenuBuilder.EndSection();
}

void FSimpleFtpToolModule::CreateToFTPServer()
{
	const FString FTPConfig = FPaths::ProjectConfigDir() + TEXT("FtpAccountInfo.ini");
	FString IP = "";
	int32 Port = 0;
	FString UserName = "";
	FString Password = "";
	if (GConfig)
	{
		GConfig->GetString(TEXT("FtpAccount"), TEXT("IP"), IP, FTPConfig);
		GConfig->GetInt(TEXT("FtpAccount"), TEXT("Port"), Port, FTPConfig);
		GConfig->GetString(TEXT("FtpAccount"), TEXT("UserName"), UserName, FTPConfig);
		GConfig->GetString(TEXT("FtpAccount"), TEXT("Password"), Password, FTPConfig);
	}

	check(FTP_INSTANCE->FTP_CreateControlSocket(IP, Port));
	check(FTP_INSTANCE->FTP_SendCommand(EFtpCommandType::USER, UserName));
	check(FTP_INSTANCE->FTP_SendCommand(EFtpCommandType::PASS, Password));

}

void FSimpleFtpToolModule::CreateInstanceFolder(TArray<FString> NewPaths)
{
	FString InsName = GetDefault<UFtpConfig>()->InsProjectName;
	if (InsName.IsEmpty() || InsName.Contains(" ") || InsName.Contains(".") || InsName.Contains("_"))
	{
		FText DialogText = FText::Format(
			LOCTEXT("Create Instance DialogText", " the instance name is wrong.\n please set '{0}' correctly in project settings.\n can not contain spaces, underscores'_', chinese and dots'.'"),
			FText::FromString(TEXT("InsProjectName"))
		);
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
		return;
	}
	FTP_INSTANCE->CreateInstanceFolder(InsName);
}

void FSimpleFtpToolModule::SubmitSourceUnderTheFolder(TArray<FString> NewPaths)
{
	TArray<FString> NameNotValidFiles;
	TArray<FInvalidDepInfo> DepenNotValidFiles;
	bool bUploadSuccess = true;
	FString FolderStr;
	for (const auto& Temp : NewPaths)
	{
		FolderStr += Temp + TEXT("\n");
		if (!FTP_INSTANCE->FTP_UploadFilesByFolder(Temp, NameNotValidFiles, DepenNotValidFiles))
			bUploadSuccess = false;
	}
	if (bUploadSuccess)
	{
		FText DialogText = FText::Format(
			LOCTEXT("Upload Folder DialogText", " Upload \n\n{0}\n Asset Successful!"),
			FText::FromString(FolderStr)
		);
		FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	}
}

void FSimpleFtpToolModule::CheckNameAndGenerateDependencyFiles(TArray<FString> NewPaths)
{	
	TArray<FString> NameNotValid;
	TArray<FInvalidDepInfo> DepenNotValidFiles;
	bool bAllNameValid = true;
	for (const auto& temp : NewPaths)
	{
		FString CopyTemp = temp;
		CopyTemp.RemoveFromStart(TEXT("/Game/"));
		FString FullPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() / CopyTemp);
		TArray<FString> ChildrenFolders;
		IFileManager::Get().FindFilesRecursive(ChildrenFolders, *FullPath, TEXT("*"), false, true);
		if (ChildrenFolders.Num())
		{
			for (const auto& tempchild : ChildrenFolders)
			{
				if (!FTP_INSTANCE->FileNameValidationOfOneFolder(NameNotValid, tempchild))
					bAllNameValid = false;
			}
		}
		else
		{
			if(!FTP_INSTANCE->FileNameValidationOfOneFolder(NameNotValid, FullPath))
				bAllNameValid = false;
		}
	}
	for(const auto& temp : NewPaths)
	{
		FTP_INSTANCE->ValidationAllDependenceOfTheFolder(temp,DepenNotValidFiles, bAllNameValid);
	}
	FTP_INSTANCE->ShowMessageBox(NameNotValid, DepenNotValidFiles);
}

void FSimpleFtpToolModule::SubmitSelectedSource(TArray<FString> NewPaths)
{
	TArray<FString> NameNotValidFiles;
	TArray<FInvalidDepInfo> DepenNotValidFiles;
	FTP_INSTANCE->FTP_UploadFilesByAsset(NewPaths, NameNotValidFiles, DepenNotValidFiles);
}

void FSimpleFtpToolModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(SimpleFtpToolTabName);
}

void FSimpleFtpToolModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FSimpleFtpToolCommands::Get().OpenPluginWindow);
}

void FSimpleFtpToolModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FSimpleFtpToolCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSimpleFtpToolModule, SimpleFtpTool)