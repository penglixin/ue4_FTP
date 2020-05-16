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
#include "FtpClient/FtpClient.h"

static const FName SimpleFtpToolTabName("SimpleFtpTool");

#define LOCTEXT_NAMESPACE "FSimpleFtpToolModule"

void FSimpleFtpToolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
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