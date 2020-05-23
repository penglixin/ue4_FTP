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
	//自定义菜单 文件夹
	TSharedRef<FExtender> OnExtendContentBrowser(const TArray<FString>& NewPaths);
	void CreateSubMenuForContentBrowser(FMenuBuilder& MenuBuilder, TArray<FString> NewPaths);  //不能传引用，只能内存拷贝

	//自定义菜单 资源
	TSharedRef<FExtender> OnExtendContentAssetBrowser(const TArray<FAssetData>& NewAssetPaths);
	void CreateSubMenuForAssetBrowser(FMenuBuilder& MenuBuilder, TArray<FString> NewPaths);  //不能传引用，只能内存拷贝


private:

	void CreateToFTPServer();

	//自定义菜单按钮点击事件 (创建实例文件夹)
	void CreateInstanceFolder(TArray<FString> NewPaths);
	//自定义菜单按钮点击事件 （提交文件夹下的资源）
	void SubmitSourceUnderTheFolder(TArray<FString> NewPaths);
	//为文件夹下的资源生成依赖文件
	void CheckNameAndGenerateDependencyFiles(TArray<FString> NewPaths);

	//自定义菜单按钮点击事件 （提交选中的资源）
	void SubmitSelectedSource(TArray<FString> NewPaths);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
