#pragma once

#include "ROSBridgeMsg.h"
#include "std_msgs/Header.h"
#include "Base64.h"

namespace sensor_msgs
{
	class CompressedImage : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		FString Format;
		TArray<uint8> Data;

	public:

		CompressedImage()
		{
			MsgType = "sensor_msgs/CompressedImage";
		}

		CompressedImage
		(std_msgs::Header InHeader, FString InFormat, const TArray<uint8>& InData)
			:
			Header(InHeader),
			Format(InFormat),
			Data(InData)
		{
			MsgType = "sensor_msgs/CompressedImage";
		}

		~CompressedImage() override {}

		std_msgs::Header GetHeader() const 
		{
			return Header;
		}

		FString GetFormat() const 
		{
			return Format;
		}

		TArray<uint8> GetData() const 
		{
			return Data; 
		}

		void SetHeader(std_msgs::Header InHeader) 
		{ 
			Header = InHeader; 
		}

        void SetFormat(FString InFormat) 
		{
			Format = InFormat;
		} 

		void SetData(const TArray<uint8>& InData) 
		{
			Data = InData; 
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Format = JsonObject->GetStringField(TEXT("format"));
			Data.Empty();
			FBase64::Decode(JsonObject->GetStringField(TEXT("data")), Data);
		}

		static CompressedImage GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			CompressedImage Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString DataString = "[ ";
			for (auto &value : Data)
				DataString += FString::FromInt(value) + TEXT(", ");
			DataString += " ]";

			return TEXT("CompressedImage { header = ") + Header.ToString() +
				TEXT(", format = ") + Format +
				TEXT(", data = ") + DataString +
				TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetStringField(TEXT("format"), Format);
			Object->SetStringField(TEXT("data"), *(FBase64::Encode(Data)));

			return Object;
		}

		virtual FString ToYamlString() const override 
		{
			FString OutputString;
			TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
			return OutputString;
		}
	};
} // namespace sensor_msgs