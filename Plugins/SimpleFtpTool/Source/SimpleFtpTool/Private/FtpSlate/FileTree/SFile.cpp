#include "FtpSlate/FileTree/SFile.h"
#include "CoreStyle.h"
#include "EditorStyleSet.h"
#include "Widgets/Input/SButton.h"
#include "Engine/StaticMesh.h"
#include "FtpSlate/FtpViewType.h"
#include "KismetProceduralMeshLibrary.h"
#include "ProceduralMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Engine/World.h"
#include "SimpleFtpTool.h"

#define LOCTEXT_NAMESPACE "File"

void SFile::Construct(const FArguments& InArgs, const SimpleFtpFile::FFileList& FileList)
{
	AssetPath = FileList.Filename;
	{
		AssetPath.RemoveFromEnd(FPaths::GetExtension(FileList.Filename, true));
	}
	//   /Game/SS/A.usset
	FString AssetName = FPackageName::GetShortName(FileList.Filename);
	ChildSlot
		[
			SNew(SButton)
			.Text(FText::Format(LOCTEXT("AnalyzingFilename", "{0}"), FText::FromString(AssetName)))
			.HAlign(HAlign_Fill)
			.OnClicked(this, &SFile::OnClicked)
			.ButtonStyle(FCoreStyle::Get(), "NoBorder")
			.TextStyle(FEditorStyle::Get(), "FlatButton.DefaultTextStyle")
		];
}

FReply SFile::OnClicked()
{
	//点击文件 渲染对应资源
	if (!AssetPath.IsEmpty())
	{
		if (GMeshComponent && GProceduralMeshComponent)
		{
			if (GProceduralMeshComponent)
			{
				GProceduralMeshComponent->ClearAllMeshSections();
			}
			FSimpleFtpToolModule& FtpModule = FModuleManager::LoadModuleChecked<FSimpleFtpToolModule>(TEXT("SimpleFtpTool"));
			UStaticMesh* staticmesh = FtpModule.StaticLoadObjectFromCache<UStaticMesh>(TEXT("Com_StaticMesh/Mat_wood_7_de"));
			if (staticmesh)
			{
				GMeshComponent->SetStaticMesh(staticmesh);
			}
		}
	}
	return FReply::Handled();
}



#undef LOCTEXT_NAMESPACE