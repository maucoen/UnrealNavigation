#pragma once
#include "ROSBridgeMsg.h"

namespace geometry_msgs
{
	class PolyTraj : public FROSBridgeMsg
	{


        uint64 timestamp;          // timestamp when the trajectory was generated
        uint16 n_segs;           //number of segments
        TArray<float>() x_coeffs;      // x polynomial coefficients, segment by segment, starting at highest order coefficient
        TArray<float>() y_coeffs;      //y polynomial coefficients, segment by segment, starting at highest order coefficient
        TArray<float>() z_coeffs;      // z polynomial coefficients, segment by segment, starting at highest order coefficient
        TArray<float>() yaw_coeffs;    // yaw polynomial coefficients, segment by segment, starting at highest order coefficient
        TArray<float>() t_trans;       // transition times, segment by segment
        uint8 n_x_coeffs;        // number of coefficients per segment for x
        uint8 n_y_coeffs;        // number of coefficients per segment for y
        uint8 n_z_coeffs;        // number of coefficients per segment for z
        uint8 n_yaw_coeffs;      // number of coefficients per segment for yaw

	public:
		PolyTraj()
		{
			MsgType = "geometry_msgs/PolyTraj";
		}

		~PolyTraj() override {}


		uint64 GetTimestamp() const
		{
			return timestamp;
		}

		uint16 GetNSegs() const
		{
			return n_segs;
		}

        TArray<float> GetXCoeffs() const
		{
			return x_coeffs;
		}

        TArray<float> GetYCoeffs() const
		{
			return y_coeffs;
		}

        TArray<float> GetYCoeffs() const
		{
			return y_coeffs;
		}

        TArray<float> GetZCoeffs() const
		{
			return z_coeffs;
		}

        TArray<float> GetYawCoeffs() const
		{
			return yaw_coeffs;
		}
        
        TArray<float> GetTTrans() const
		{
			return t_trans;
		}

		// geometry_msgs::Point32 GetPointAt(uint32 Index)
		// {
		// 	check(Index < Points.Num());
		// 	return Points[Index];
		// }

		uint8 GetNXCoeffs() const
		{
			return n_x_coeffs;
		}

        uint8 GetNYCoeffs() const
		{
			return n_y_coeffs;
		}

        uint8 GetNZCoeffs() const
		{
			return n_z_coeffs;
		}

        uint8 GetNYawCoeffs() const
		{
			return n_yaw_coeffs;
		}

        virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
            timestamp = (uint64)(JsonObject->GetNumberField(TEXT("timestamp")));
            n_segs = (uint16)(JsonObject->GetNumberField(TEXT("n_segs")));
			
			x_coeffs.Empty();
			TArray<TSharedPtr<FJsonValue>> PtrArr = JsonObject->GetArrayField(TEXT("x_coeffs"));
			for (auto &ptr : PtrArr)
            {
                x_coeffs.Add(ptr->AsNumber());
            }

            y_coeffs.Empty();
			TArray<TSharedPtr<FJsonValue>> PtrArr = JsonObject->GetArrayField(TEXT("y_coeffs"));
			for (auto &ptr : PtrArr)
            {
                y_coeffs.Add(ptr->AsNumber());
            }

            z_coeffs.Empty();
			TArray<TSharedPtr<FJsonValue>> PtrArr = JsonObject->GetArrayField(TEXT("z_coeffs"));
			for (auto &ptr : PtrArr)
            {
                z_coeffs.Add(ptr->AsNumber());
            }

            yaw_coeffs.Empty();
			TArray<TSharedPtr<FJsonValue>> PtrArr = JsonObject->GetArrayField(TEXT("yaw_coeffs"));
			for (auto &ptr : PtrArr)
            {
                yaw_coeffs.Add(ptr->AsNumber());
            }

            t_trans.Empty();
			TArray<TSharedPtr<FJsonValue>> PtrArr = JsonObject->GetArrayField(TEXT("t_trans"));
			for (auto &ptr : PtrArr)
            {
                t_trans.Add(ptr->AsNumber());
            }

            n_x_coeffs = (uint16)(JsonObject->GetNumberField(TEXT("n_x_coeffs")));
            n_y_coeffs = (uint16)(JsonObject->GetNumberField(TEXT("n_y_coeffs")));
            n_z_coeffs = (uint16)(JsonObject->GetNumberField(TEXT("n_z_coeffs")));
            n_yaw_coeffs = (uint16)(JsonObject->GetNumberField(TEXT("n_yaw_coeffs")));
				
		}

		static PolyTraj GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PolyTraj Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			// return TEXT("PolyTraj { x = ") + FString::SanitizeFloat(X) +
			// 	TEXT(", y = ") + FString::SanitizeFloat(Y) +
			// 	TEXT(", z = ") + FString::SanitizeFloat(Z) + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
        {
			// TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			// Object->SetNumberField(TEXT("x"), X);
			// Object->SetNumberField(TEXT("y"), Y);
			// Object->SetNumberField(TEXT("z"), Z);
			// return Object;
		}

		virtual FString ToYamlString() const override 
		{
			// FString OutputString;
			// TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
			// FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
			// return OutputString;
		}
	};
} // geometry_msgs