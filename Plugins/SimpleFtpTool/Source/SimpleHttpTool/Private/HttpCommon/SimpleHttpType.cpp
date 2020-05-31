#include "HttpCommon/SimpleHttpType.h"

FString FWebSendData::ConvertToString()
{
	FString Json;
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Json);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue(TEXT("name"), this->name);
	JsonWriter->WriteValue(TEXT("describe"), this->describe);
	JsonWriter->WriteValue(TEXT("filePath"), this->filePath);
	JsonWriter->WriteValue(TEXT("file"), this->file);
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	return Json;
}
