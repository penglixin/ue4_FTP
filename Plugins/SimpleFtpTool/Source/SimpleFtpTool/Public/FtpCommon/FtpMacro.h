// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#define PASV_MODE 227   //成功设置为被动模式
#define LIST_SUCCEED 150  //打开数据控制通道成功
#define ERROR_DIRECTORY 550  //LIST失败 没有路径
#define SUCCEED_TRANSFER 226  //上传，下载成功


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
	for (const auto& TempAeestType : AssetTypes)\
	{\
		FString UperAssetType = TempAeestType.ToUpper();\
		FString l, r;\
		UperAssetType.Split(TEXT(":"), &l, &r);\
		if (!(partArr[1].Equals(l)) && !(partArr[1].Equals(r)))\
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


