#include "FtpSlate/FileTree/SFolder.h"
#include "FtpSlate/FileTree/SFile.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Input/SButton.h"
#include "EditorStyleSet.h"
#include "CoreStyle.h"
#include "Misc/App.h"

#define LOCTEXT_NAMESPACE "Folder"

void SFolder::Construct(const FArguments& InArgs, const SimpleFtpFile::FFileList& FileList)
{
	TSharedPtr<SVerticalBox> FileArray = SNew(SVerticalBox);
	FolderName = FileList.Filename;
	for (const auto& Tmp : FileList.Children)
	{
		if (Tmp.GetFileType() == SimpleFtpFile::EFileType::FOLDER)
		{
			FileArray->AddSlot()
				.AutoHeight()
				[
					SNew(SFolder, Tmp)
				];
		}
		else
		{
			FileArray->AddSlot()
				.AutoHeight()
				[
					SNew(SFile, Tmp)
				];
		}
	}
	if (FolderName.Contains(TEXT("Ins")) || FolderName.Equals(FApp::GetProjectName()))
	{
		ChildSlot
			[
				SAssignNew(Area, SExpandableArea)
				.BorderBackgroundColor(FLinearColor::Transparent)
				.InitiallyCollapsed(false)
				.Padding(FMargin(0.0f, 1.0f, 0.0f, 8.0f))
				.HeaderContent()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SImage)
						.Image(this, &SFolder::GetFileTypeICO)
					]
					+ SHorizontalBox::Slot()
					.VAlign(VAlign_Center)
					.AutoWidth()
					[
						SNew(STextBlock)
						.Text(FText::Format(LOCTEXT("AnalyzingFilename", "{0}"), FText::FromString(FileList.Filename)))
					]
				]
			.BodyContent()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SSpacer)
						.Size(FVector2D(20.f, 1.f))
					]
				+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						FileArray.ToSharedRef()
					]
				]
			];
	}
	else
	{
		ChildSlot
			[
				SAssignNew(Area, SExpandableArea)
				.BorderBackgroundColor(FLinearColor::Transparent)
				.InitiallyCollapsed(false)
				.Padding(FMargin(0.0f, 1.0f, 0.0f, 8.0f))
				.HeaderContent()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SImage)
					.Image(this, &SFolder::GetFileTypeICO)
				]
				+ SHorizontalBox::Slot()
					.VAlign(VAlign_Center)
					.AutoWidth()
					[
						SNew(STextBlock)
						.Text(FText::Format(LOCTEXT("AnalyzingFilename", "{0}"), FText::FromString(FileList.Filename)))
					]
				+ SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					[
						SNew(SSpacer)
						.Size(FVector2D(20.f, 10.f))
					]
				+ SHorizontalBox::Slot()
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Right)
					.AutoWidth()
					[
						SNew(SButton)
						.Text(FText::Format(LOCTEXT("AnalyzingButton", "{0}"), FText::FromString(TEXT("Download"))))
					.HAlign(HAlign_Right)
					.OnClicked(this, &SFolder::OnClicked)
					.ButtonStyle(FCoreStyle::Get(), "Border")
					.TextStyle(FEditorStyle::Get(), "FlatButton.DefaultTextStyle")
					]
					]
				.BodyContent()
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
					[
						SNew(SSpacer)
						.Size(FVector2D(20.f, 1.f))
					]
				+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						FileArray.ToSharedRef()
					]
					]
				];
	}
}

const FSlateBrush* SFolder::GetFileTypeICO() const
{
	return Area->IsExpanded() ?
		FEditorStyle::Get().GetBrush(TEXT("SceneOutliner.FolderOpen")) :
		FEditorStyle::Get().GetBrush(TEXT("SceneOutliner.FolderClosed"));
}

FReply SFolder::OnClicked()
{
	FString ServerFolderPath = TEXT("/") + FolderName;
	if (!FolderName.Contains(TEXT("Com_")))
	{
		ServerFolderPath = TEXT("/Instance/") + FolderName;
	}
	GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Yellow, ServerFolderPath);
	//文件夹下载只能下载公共资源文件夹，实例文件夹，第三方资源文件夹

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE