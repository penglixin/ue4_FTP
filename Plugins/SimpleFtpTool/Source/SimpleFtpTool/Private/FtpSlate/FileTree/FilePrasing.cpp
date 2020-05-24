#include "FtpSlate/FileTree/FilePrasing.h"
#include "Misc/App.h"

SimpleFtpFile::EFileType SimpleFtpFile::FFileList::GetFileType() const
{
	return Filename.Contains(TEXT(".")) ? EFileType::FILE : EFileType::FOLDER;
}

void SimpleFtpFile::FilesParsing(const TArray<FString>& Filenames, FFileList& List)
{
	/*	Com_Material/Mat_pp_1_sd1.dep
		Com_Material/Mat_pp_1_sd1.uasset
		Instance/ProjD/Ins_Material/Mat_pp_0_sd.dep
		Instance/ProjD/Ins_Material/Mat_pp_0_sd.uasset
	*/
	FFileList* FileList = &List;
	FileList->Filename = FApp::GetProjectName();
	for (const auto& Filename : Filenames)
	{
		TArray<FString> FileLevel;
		Filename.ParseIntoArray(FileLevel, TEXT("/"));

		FileList = &List;
		for (const auto& TmpFile : FileLevel)
		{
			FFileList FileListElement;
			FileListElement.Filename = TmpFile;
			int32 i = FileList->Children.AddUnique(FileListElement);
			FileList = &(FileList->Children[i]);
		}
		FileList->Filename = Filename;
	}

}
