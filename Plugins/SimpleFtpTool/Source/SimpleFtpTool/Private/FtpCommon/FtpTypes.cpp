#include "FtpCommon/FtpTypes.h"
#include "Json.h"

#if WITH_EDITOR
#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif
#endif


void SimpleFtpDataType::ConvertStructToString(const FDataInfoList& TypeArr, FString& Json)
{
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Json);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue(TEXT("FILEEDESCRIPTION"), TypeArr.FILEEDESCRIPTION);
	JsonWriter->WriteArrayStart(TEXT("DATATYPRARR"));
	for (const auto& temptype : TypeArr.DATATYPRARR)
	{
		JsonWriter->WriteObjectStart();
		JsonWriter->WriteValue(TEXT("TYPENAME"), temptype.TYPENAME);
		JsonWriter->WriteValue(TEXT("TYPEABBR"), temptype.TYPEABBR);
		JsonWriter->WriteValue(TEXT("TYPEDESCRIPTION"), temptype.TYPEDESCRIPTION);
		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteArrayEnd();
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
}

bool SimpleFtpDataType::ConvertStringToStruct(const FString& Json, FDataInfoList& TypeArr)
{
	bool bSuccessed = true;
	TSharedPtr<FJsonValue> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Json);
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		const TSharedPtr<FJsonObject> JsonObject = JsonParsed->AsObject();
		if (!JsonObject->TryGetStringField(TEXT("FILEEDESCRIPTION"), TypeArr.FILEEDESCRIPTION))
		{
			bSuccessed = false;
		}
		const TArray<TSharedPtr<FJsonValue>>* JsonArray;
		if (!JsonObject->TryGetArrayField(TEXT("DATATYPRARR"), JsonArray))
			bSuccessed = false;
		else
		{
			if (JsonArray)
			{
				for (const auto& temp : *JsonArray)
				{
					const TSharedPtr<FJsonObject> TempJsonObject = temp->AsObject();
					FDataTypeInfo info;
					if (!TempJsonObject->TryGetStringField(TEXT("TYPENAME"), info.TYPENAME))
					{
						bSuccessed = false;
					}
					if (!TempJsonObject->TryGetStringField(TEXT("TYPEABBR"), info.TYPEABBR))
					{
						bSuccessed = false;
					}
					if (!TempJsonObject->TryGetStringField(TEXT("TYPEDESCRIPTION"), info.TYPEDESCRIPTION))
					{
						bSuccessed = false;
					}
					TypeArr.DATATYPRARR.Add(info);
				}
			}
		}
	}
	return bSuccessed;
}

void SimpleFtpDataType::ConvertStructToString(const FDependenList& DepenArr, FString& Json)
{
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Json);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue(TEXT("SourceAssetName"), DepenArr.SourceAssetName);
	JsonWriter->WriteValue(TEXT("LastModifyTime"), DepenArr.LastModifyTime);
	JsonWriter->WriteValue(TEXT("ValidCode"), DepenArr.ValidCode);
	JsonWriter->WriteArrayStart(TEXT("DepenArr"));
	for (const auto& tempdepen : DepenArr.DepenArr)
	{
		JsonWriter->WriteObjectStart();
		JsonWriter->WriteValue(TEXT("DepenAssetPackName"), tempdepen.DepenAssetPackName);
		JsonWriter->WriteValue(TEXT("ValidCode"), tempdepen.ValidCode);
		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteArrayEnd();
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
}

bool SimpleFtpDataType::ConvertStringToStruct(const FString& Json, FDependenList& DepenArr)
{
	bool bSuccessed = true;
	TSharedPtr<FJsonValue> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Json);
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		const TSharedPtr<FJsonObject> JsonObject = JsonParsed->AsObject();
		if (!JsonObject->TryGetStringField(TEXT("SourceAssetName"), DepenArr.SourceAssetName))
		{
			bSuccessed = false;
		}
		if (!JsonObject->TryGetStringField(TEXT("LastModifyTime"), DepenArr.LastModifyTime))
		{
			bSuccessed = false;
		}
		if (!JsonObject->TryGetStringField(TEXT("ValidCode"), DepenArr.ValidCode))
		{
			bSuccessed = false;
		}
		const TArray<TSharedPtr<FJsonValue>>* JsonArray;
		if (!JsonObject->TryGetArrayField(TEXT("DepenArr"), JsonArray))
			bSuccessed = false;
		else
		{
			if (JsonArray)
			{
				for (const auto& temp : *JsonArray)
				{
					const TSharedPtr<FJsonObject> TempJsonObject = temp->AsObject();
					FDependenceInfo info;
					if (!TempJsonObject->TryGetStringField(TEXT("DepenAssetPackName"), info.DepenAssetPackName))
					{
						bSuccessed = false;
					}
					if (!TempJsonObject->TryGetStringField(TEXT("ValidCode"), info.ValidCode))
					{
						bSuccessed = false;
					}
					DepenArr.DepenArr.Add(info);
				}
			}
		}
	}
	return bSuccessed;
}

void SimpleFtpDataType::ConvertStructToString(const FInstanceInfo& InstInfo, FString& Json)
{
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Json);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue(TEXT("InstValidCode"), InstInfo.InstValidCode);

	JsonWriter->WriteArrayStart(TEXT("CommonAssetPackageName"));
	for (const auto& temp : InstInfo.CommonAssetPackageName)
	{
		JsonWriter->WriteObjectStart();
		JsonWriter->WriteValue(TEXT("CommonAsset"), temp);
		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteArrayEnd();

	JsonWriter->WriteArrayStart(TEXT("ThirdPartyAssetPackageName"));
	for (const auto& temp : InstInfo.ThirdPartyAssetPackageName)
	{
		JsonWriter->WriteObjectStart();
		JsonWriter->WriteValue(TEXT("ThirdAsset"), temp);
		JsonWriter->WriteObjectEnd();
	}
	JsonWriter->WriteArrayEnd();

	JsonWriter->WriteObjectEnd(); 
	JsonWriter->Close();
}

bool SimpleFtpDataType::ConvertStringToStruct(const FString& Json, FInstanceInfo& InstInfo)
{
	bool bSuccessed = true;
	TSharedPtr<FJsonValue> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Json);
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		const TSharedPtr<FJsonObject> JsonObject = JsonParsed->AsObject();
		if (!JsonObject->TryGetStringField(TEXT("InstValidCode"), InstInfo.InstValidCode))
		{
			bSuccessed = false;
		}
		const TArray<TSharedPtr<FJsonValue>>* JsonArray1;
		if (!JsonObject->TryGetArrayField(TEXT("CommonAssetPackageName"), JsonArray1))
			bSuccessed = false;
		else
		{
			if (JsonArray1)
			{
				for (const auto& temp : *JsonArray1)
				{
					const TSharedPtr<FJsonObject> TempJsonObject = temp->AsObject();
					FString CommonPackName;
					if (!TempJsonObject->TryGetStringField(TEXT("CommonAsset"), CommonPackName))
					{
						bSuccessed = false;
					}
					InstInfo.CommonAssetPackageName.Add(CommonPackName);
				}
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* JsonArray2;
		if (!JsonObject->TryGetArrayField(TEXT("ThirdPartyAssetPackageName"), JsonArray2))
			bSuccessed = false;
		else
		{
			if (JsonArray2)
			{
				for (const auto& temp : *JsonArray2)
				{
					const TSharedPtr<FJsonObject> TempJsonObject = temp->AsObject();
					FString ThirdPackName;
					if (!TempJsonObject->TryGetStringField(TEXT("ThirdAsset"), ThirdPackName))
					{
						bSuccessed = false;
					}
					InstInfo.ThirdPartyAssetPackageName.Add(ThirdPackName);
				}
			}
		}
	}
	return bSuccessed;
}



void FDependenList::Empty()
{
	SourceAssetName = "";
	LastModifyTime = "";
	DepenArr.Empty();
}

void FInstanceInfo::Empty()
{
	InstValidCode = "";
	CommonAssetPackageName.Empty();
	ThirdPartyAssetPackageName.Empty();
}

#if WITH_EDITOR
#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif
#endif


