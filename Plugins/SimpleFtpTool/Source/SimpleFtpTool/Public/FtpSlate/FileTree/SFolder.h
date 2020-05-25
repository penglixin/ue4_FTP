// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "FtpSlate/FileTree/FilePrasing.h"

class SFolder :public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFolder)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const SimpleFtpFile::FFileList& FileList);

	const FSlateBrush* GetFileTypeICO() const;

	FReply OnClicked();

private:
	TSharedPtr<class SExpandableArea> Area;
	FString FolderName;
};