#include "FtpCommon/FtpTypes.h"
#include "Json.h"

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif


void SimpleDataType::ConvertStructToString(const DataList& TypeArr, FString& Json)
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

bool SimpleDataType::ConvertStringToStruct(const FString& Json, DataList& TypeArr)
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


#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif

