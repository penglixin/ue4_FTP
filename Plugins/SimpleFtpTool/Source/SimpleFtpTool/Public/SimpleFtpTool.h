// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FSimpleFtpToolModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	//自定义菜单
	TSharedRef<FExtender> OnExtendContentBrowser(const TArray<FString>& NewPaths);
	void CreateSubMenuForContentBrowser(FMenuBuilder& MenuBuilder, TArray<FString> NewPaths);  //不能传引用，只能内存拷贝

private:
	//自定义菜单按钮点击事件
	void CreateInstanceFolder(TArray<FString> NewPaths);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
