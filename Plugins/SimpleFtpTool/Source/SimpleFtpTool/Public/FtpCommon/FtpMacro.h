// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#define PASV_MODE 227   //成功设置为被动模式
#define LIST_SUCCEED 150  //打开数据控制通道成功
#define ERROR_DIRECTORY 550  //LIST失败 没有路径
#define SUCCEED_TRANSFER 226  //上传，下载成功
#define FILE_EXIST 213  //判断文件是否存在于服务器

#define NAME_VALIDATION_FOLDER(Prefix)  \
for (const auto& TempName : AllFileNames)\
{\
	FString UperFileName = TempName.ToUpper();\
	numArr1.Add(TempName);\
	TArray<FString> partArr;\
	UperFileName.ParseIntoArray(partArr, TEXT("_"), false);\
	if (partArr.Num() != 4)\
	{\
		bAllValid = false;\
		NoValidFiles.Add(TempName);\
		numArr2.Add(FGuid::NewGuid().ToString());\
		continue;\
	}\
	if (!partArr[0].Equals(TEXT(##Prefix)))\
	{\
		bAllValid = false;\
		NoValidFiles.Add(TempName);\
		numArr2.Add(FGuid::NewGuid().ToString());\
		continue;\
	}\
	bool bCorrect = false;\
	for (const auto& TempAeestType : InfoList.DATATYPRARR)\
	{\
		if (!(partArr[1].Equals(TempAeestType.TYPENAME)) && !(partArr[1].Equals(TempAeestType.TYPEABBR)))\
		{\
			continue;\
		}\
		else\
		{\
			bCorrect = true;\
			break;\
		}\
	}\
	if (!bCorrect)\
	{\
		bAllValid = false;\
		NoValidFiles.Add(TempName);\
		numArr2.Add(FGuid::NewGuid().ToString());\
		continue;\
	}\
	numArr2.AddUnique(partArr[2]);\
	if (numArr1.Num() != numArr2.Num())\
	{\
		bAllValid = false;\
		NoValidFiles.Add(TempName);\
		numArr2.Add(FGuid::NewGuid().ToString());\
	}\
}



#define NAME_VALIDATION_ASSET(Prefix)\
UperFileName = AssetName.ToUpper(); \
numArr1.Add(AssetName);\
UperFileName.ParseIntoArray(partArr, TEXT("_"), false);\
if (partArr.Num() != 4)\
{\
	bAllValid = false;\
	NameNotValidFiles.Add(AssetName);\
	numArr2.Add(FGuid::NewGuid().ToString());\
	continue;\
}\
if (!partArr[0].Equals(TEXT(##Prefix)))\
{\
	bAllValid = false;\
	NameNotValidFiles.Add(AssetName);\
	numArr2.Add(FGuid::NewGuid().ToString());\
	continue;\
}\
for (const auto& TempAeestType : InfoList.DATATYPRARR)\
{\
	if (!(partArr[1].Equals(TempAeestType.TYPEABBR)) && !(partArr[1].Equals(TempAeestType.TYPENAME)))\
	{\
		continue;\
	}\
	else\
	{\
		bCorrect = true;\
		continue;\
	}\
}\
if (!bCorrect)\
{\
	bAllValid = false;\
	NameNotValidFiles.Add(AssetName);\
	numArr2.Add(FGuid::NewGuid().ToString());\
	continue;\
}\
numArr2.AddUnique(partArr[2]);\
if (numArr1.Num() != numArr2.Num())\
{\
	bAllValid = false;\
	NameNotValidFiles.Add(AssetName);\
	numArr2.Add(FGuid::NewGuid().ToString());\
}\
break


#define GENERATE_DEP_FILE()\
bDepHasChanged = true; \
depenlist.Empty();\
depenlist.SourceAssetName = AssetPackName;\
depenlist.ValidCode = FGuid::NewGuid().ToString();\
for (const auto& temp : TheAssetDependence)\
{\
	FDependenceInfo OneInfo;\
	OneInfo.DepenAssetPackName = temp;\
	OneInfo.ValidCode = FGuid::NewGuid().ToString();\
	depenlist.DepenArr.Add(OneInfo);\
}\
FDateTime DataTime = IFileManager::Get().GetTimeStamp(*UAssetName);\
depenlist.LastModifyTime = ConvertTimeToStr(DataTime);\
SimpleFtpDataType::ConvertStructToString(depenlist, Json);\
FFileHelper::SaveStringToFile(Json, *FileName)



#define GENERATE_INST_FILE()\
InstInfo.InstValidCode = FGuid::NewGuid().ToString();\
for (const auto& temp : AllDependences)\
{\
	if (temp.Contains("/Com_")) \
	{\
		InstInfo.CommonAssetPackageName.Add(temp);\
	}\
	else if (!temp.Contains("/Instance/")) \
	{\
		InstInfo.ThirdPartyAssetPackageName.Add(temp);\
	}\
}\
SimpleFtpDataType::ConvertStructToString(InstInfo, Json);\
FFileHelper::SaveStringToFile(Json, *InstConfigName)


#define GET_ASSET_VALIDCODE()\
if (IFileManager::Get().FileExists(*DepLocalFullPath))\
{\
	FFileHelper::LoadFileToString(Json, *DepLocalFullPath);\
	if (SimpleFtpDataType::ConvertStringToStruct(Json, DepInfo))\
	{\
		LocalValidCode = DepInfo.ValidCode;\
	}\
	if (FTP_DownloadOneFile(DepServerPath,GetDefault<UFtpConfig>()->CachePath.Path))\
	{\
		Json.Empty();\
		DepInfo.Empty();\
		FString DepCachePath = GetDefault<UFtpConfig>()->CachePath.Path + TEXT("/") + DepServerPath;\
		FFileHelper::LoadFileToString(Json, *DepCachePath);\
		if (SimpleFtpDataType::ConvertStringToStruct(Json, DepInfo))\
		{\
			ServerValidCode = DepInfo.ValidCode;\
		}\
		IFileManager::Get().Delete(*DepCachePath);\
	}\
}\
else\
{\
	return false;\
}


#define GET_INST_VALIDCODE()\
if (IFileManager::Get().FileExists(*localfilename))\
{\
	FFileHelper::LoadFileToString(Json, *localfilename);\
	if (SimpleFtpDataType::ConvertStringToStruct(Json, instInfo))\
	{\
		LocalValidCode = instInfo.InstValidCode;\
	}\
}\
else\
{\
	return false;\
}\
if (FTP_DownloadOneFile(serverfilename,GetDefault<UFtpConfig>()->CachePath.Path))\
{\
	Json.Empty();\
	instInfo.Empty();\
	FString DepCachePath = GetDefault<UFtpConfig>()->CachePath.Path + TEXT("/") + serverfilename;\
	FFileHelper::LoadFileToString(Json, *DepCachePath);\
	if (SimpleFtpDataType::ConvertStringToStruct(Json, instInfo))\
	{\
		ServerValidCode = instInfo.InstValidCode;\
	}\
	IFileManager::Get().Delete(*DepCachePath); \
}

