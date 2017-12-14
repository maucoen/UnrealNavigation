// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "GameLiftClientSDK.generated.dep.h"
PRAGMA_DISABLE_OPTIMIZATION
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCode1GameLiftClientSDK() {}
#if USE_COMPILED_IN_NATIVES
// Cross Module References
	COREUOBJECT_API class UClass* Z_Construct_UClass_UObject();

	GAMELIFTCLIENTSDK_API class UEnum* Z_Construct_UEnum_GameLiftClientSDK_EGameLiftGameSessionStatus();
	GAMELIFTCLIENTSDK_API class UScriptStruct* Z_Construct_UScriptStruct_FGameLiftGameSessionConfig();
	GAMELIFTCLIENTSDK_API class UScriptStruct* Z_Construct_UScriptStruct_FGameLiftGameSessionServerProperties();
	GAMELIFTCLIENTSDK_API class UFunction* Z_Construct_UFunction_UGameLiftClientObject_CreateGameLiftObject();
	GAMELIFTCLIENTSDK_API class UFunction* Z_Construct_UFunction_UGameLiftClientObject_CreateGameSession();
	GAMELIFTCLIENTSDK_API class UFunction* Z_Construct_UFunction_UGameLiftClientObject_CreatePlayerSession();
	GAMELIFTCLIENTSDK_API class UFunction* Z_Construct_UFunction_UGameLiftClientObject_DescribeGameSession();
	GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftClientObject_NoRegister();
	GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftClientObject();
	GAMELIFTCLIENTSDK_API class UFunction* Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreatePlayerSessionFailed__DelegateSignature();
	GAMELIFTCLIENTSDK_API class UFunction* Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreatePlayerSessionSuccess__DelegateSignature();
	GAMELIFTCLIENTSDK_API class UFunction* Z_Construct_UDelegateFunction_GameLiftClientSDK_OnDescribeGameSessionStateFailed__DelegateSignature();
	GAMELIFTCLIENTSDK_API class UFunction* Z_Construct_UDelegateFunction_GameLiftClientSDK_OnDescribeGameSessionStateSuccess__DelegateSignature();
	GAMELIFTCLIENTSDK_API class UFunction* Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreateGameSessionFailed__DelegateSignature();
	GAMELIFTCLIENTSDK_API class UFunction* Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreateGameSessionSuccess__DelegateSignature();
	GAMELIFTCLIENTSDK_API class UEnum* Z_Construct_UEnum_GameLiftClientSDK_EActivateStatus();
	GAMELIFTCLIENTSDK_API class UFunction* Z_Construct_UFunction_UGameLiftCreateGameSession_Activate();
	GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftCreateGameSession_NoRegister();
	GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftCreateGameSession();
	GAMELIFTCLIENTSDK_API class UFunction* Z_Construct_UFunction_UGameLiftDescribeGameSession_Activate();
	GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftDescribeGameSession_NoRegister();
	GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftDescribeGameSession();
	GAMELIFTCLIENTSDK_API class UFunction* Z_Construct_UFunction_UGameLiftCreatePlayerSession_Activate();
	GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftCreatePlayerSession_NoRegister();
	GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftCreatePlayerSession();
	GAMELIFTCLIENTSDK_API class UPackage* Z_Construct_UPackage__Script_GameLiftClientSDK();
static UEnum* EGameLiftGameSessionStatus_StaticEnum()
{
	extern GAMELIFTCLIENTSDK_API class UPackage* Z_Construct_UPackage__Script_GameLiftClientSDK();
	static UEnum* Singleton = nullptr;
	if (!Singleton)
	{
		extern GAMELIFTCLIENTSDK_API class UEnum* Z_Construct_UEnum_GameLiftClientSDK_EGameLiftGameSessionStatus();
		Singleton = GetStaticEnum(Z_Construct_UEnum_GameLiftClientSDK_EGameLiftGameSessionStatus, Z_Construct_UPackage__Script_GameLiftClientSDK(), TEXT("EGameLiftGameSessionStatus"));
	}
	return Singleton;
}
static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EGameLiftGameSessionStatus(EGameLiftGameSessionStatus_StaticEnum, TEXT("/Script/GameLiftClientSDK"), TEXT("EGameLiftGameSessionStatus"), false, nullptr, nullptr);
	UEnum* Z_Construct_UEnum_GameLiftClientSDK_EGameLiftGameSessionStatus()
	{
		UPackage* Outer=Z_Construct_UPackage__Script_GameLiftClientSDK();
		extern uint32 Get_Z_Construct_UEnum_GameLiftClientSDK_EGameLiftGameSessionStatus_CRC();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EGameLiftGameSessionStatus"), 0, Get_Z_Construct_UEnum_GameLiftClientSDK_EGameLiftGameSessionStatus_CRC(), false);
		if (!ReturnEnum)
		{
			ReturnEnum = new(EC_InternalUseOnlyConstructor, Outer, TEXT("EGameLiftGameSessionStatus"), RF_Public|RF_Transient|RF_MarkAsNative) UEnum(FObjectInitializer());
			TArray<TPair<FName, int64>> EnumNames;
			EnumNames.Emplace(TEXT("EGameLiftGameSessionStatus::STATUS_Activating"), 0);
			EnumNames.Emplace(TEXT("EGameLiftGameSessionStatus::STATUS_Active"), 1);
			EnumNames.Emplace(TEXT("EGameLiftGameSessionStatus::STATUS_Error"), 2);
			EnumNames.Emplace(TEXT("EGameLiftGameSessionStatus::STATUS_NotSet"), 3);
			EnumNames.Emplace(TEXT("EGameLiftGameSessionStatus::STATUS_Terminating"), 4);
			EnumNames.Emplace(TEXT("EGameLiftGameSessionStatus::STATUS_Terminated"), 5);
			EnumNames.Emplace(TEXT("EGameLiftGameSessionStatus::STATUS_NoStatus"), 6);
			EnumNames.Emplace(TEXT("EGameLiftGameSessionStatus::STATUS_MAX"), 7);
			ReturnEnum->SetEnums(EnumNames, UEnum::ECppForm::EnumClass);
			ReturnEnum->CppType = TEXT("EGameLiftGameSessionStatus");
#if WITH_METADATA
			UMetaData* MetaData = ReturnEnum->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnEnum, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnEnum, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientTypes.h"));
			MetaData->SetValue(ReturnEnum, TEXT("STATUS_Activating.DisplayName"), TEXT("Activating"));
			MetaData->SetValue(ReturnEnum, TEXT("STATUS_Active.DisplayName"), TEXT("Active"));
			MetaData->SetValue(ReturnEnum, TEXT("STATUS_Error.DisplayName"), TEXT("Error"));
			MetaData->SetValue(ReturnEnum, TEXT("STATUS_NoStatus.Hidden"), TEXT(""));
			MetaData->SetValue(ReturnEnum, TEXT("STATUS_NotSet.DisplayName"), TEXT("Not Set"));
			MetaData->SetValue(ReturnEnum, TEXT("STATUS_Terminated.DisplayName"), TEXT("Terminated"));
			MetaData->SetValue(ReturnEnum, TEXT("STATUS_Terminating.DisplayName"), TEXT("Terminating"));
#endif
		}
		return ReturnEnum;
	}
	uint32 Get_Z_Construct_UEnum_GameLiftClientSDK_EGameLiftGameSessionStatus_CRC() { return 1301716893U; }
class UScriptStruct* FGameLiftGameSessionConfig::StaticStruct()
{
	extern GAMELIFTCLIENTSDK_API class UPackage* Z_Construct_UPackage__Script_GameLiftClientSDK();
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern GAMELIFTCLIENTSDK_API class UScriptStruct* Z_Construct_UScriptStruct_FGameLiftGameSessionConfig();
		extern GAMELIFTCLIENTSDK_API uint32 Get_Z_Construct_UScriptStruct_FGameLiftGameSessionConfig_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FGameLiftGameSessionConfig, Z_Construct_UPackage__Script_GameLiftClientSDK(), TEXT("GameLiftGameSessionConfig"), sizeof(FGameLiftGameSessionConfig), Get_Z_Construct_UScriptStruct_FGameLiftGameSessionConfig_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FGameLiftGameSessionConfig(FGameLiftGameSessionConfig::StaticStruct, TEXT("/Script/GameLiftClientSDK"), TEXT("GameLiftGameSessionConfig"), false, nullptr, nullptr);
static struct FScriptStruct_GameLiftClientSDK_StaticRegisterNativesFGameLiftGameSessionConfig
{
	FScriptStruct_GameLiftClientSDK_StaticRegisterNativesFGameLiftGameSessionConfig()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("GameLiftGameSessionConfig")),new UScriptStruct::TCppStructOps<FGameLiftGameSessionConfig>);
	}
} ScriptStruct_GameLiftClientSDK_StaticRegisterNativesFGameLiftGameSessionConfig;
	UScriptStruct* Z_Construct_UScriptStruct_FGameLiftGameSessionConfig()
	{
		UPackage* Outer = Z_Construct_UPackage__Script_GameLiftClientSDK();
		extern uint32 Get_Z_Construct_UScriptStruct_FGameLiftGameSessionConfig_CRC();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("GameLiftGameSessionConfig"), sizeof(FGameLiftGameSessionConfig), Get_Z_Construct_UScriptStruct_FGameLiftGameSessionConfig_CRC(), false);
		if (!ReturnStruct)
		{
			ReturnStruct = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GameLiftGameSessionConfig"), RF_Public|RF_Transient|RF_MarkAsNative) UScriptStruct(FObjectInitializer(), NULL, new UScriptStruct::TCppStructOps<FGameLiftGameSessionConfig>, EStructFlags(0x00000001));
			UProperty* NewProp_GameSessionProperties = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("GameSessionProperties"), RF_Public|RF_Transient|RF_MarkAsNative) UArrayProperty(CPP_PROPERTY_BASE(GameSessionProperties, FGameLiftGameSessionConfig), 0x0040000000000005);
			UProperty* NewProp_GameSessionProperties_Inner = new(EC_InternalUseOnlyConstructor, NewProp_GameSessionProperties, TEXT("GameSessionProperties"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000, Z_Construct_UScriptStruct_FGameLiftGameSessionServerProperties());
			UProperty* NewProp_AliasID = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("AliasID"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(AliasID, FGameLiftGameSessionConfig), 0x0040000000000005);
			UProperty* NewProp_MaxPlayers = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("MaxPlayers"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(MaxPlayers, FGameLiftGameSessionConfig), 0x0040000000000005);
			ReturnStruct->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnStruct->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnStruct, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientTypes.h"));
			MetaData->SetValue(NewProp_GameSessionProperties, TEXT("AllowPrivateAccess"), TEXT("true"));
			MetaData->SetValue(NewProp_GameSessionProperties, TEXT("Category"), TEXT("GameLiftGameSessionConfig"));
			MetaData->SetValue(NewProp_GameSessionProperties, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientTypes.h"));
			MetaData->SetValue(NewProp_GameSessionProperties, TEXT("ToolTip"), TEXT("Set of developer-defined properties for a game session, formatted as a set of type:value pairs.\n       * These properties are included in the GameSession object, which is passed to the game server with a request to start a new game session"));
			MetaData->SetValue(NewProp_AliasID, TEXT("AllowPrivateAccess"), TEXT("true"));
			MetaData->SetValue(NewProp_AliasID, TEXT("Category"), TEXT("GameLiftGameSessionConfig"));
			MetaData->SetValue(NewProp_AliasID, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientTypes.h"));
			MetaData->SetValue(NewProp_AliasID, TEXT("ToolTip"), TEXT("* Unique identifier for an alias associated with the fleet to create a game session in.\n* You can switch gameplay and players to a new fleet without changing your game client or other game components.\n* For example, for games in production, using an alias allows you to seamlessly redirect your player base to a new game server update.\n* @See http://docs.aws.amazon.com/gamelift/latest/developerguide/aliases-creating.html\n* @See http://docs.aws.amazon.com/gamelift/latest/apireference/API_CreateAlias.html"));
			MetaData->SetValue(NewProp_MaxPlayers, TEXT("AllowPrivateAccess"), TEXT("true"));
			MetaData->SetValue(NewProp_MaxPlayers, TEXT("Category"), TEXT("GameLiftGameSessionConfig"));
			MetaData->SetValue(NewProp_MaxPlayers, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientTypes.h"));
			MetaData->SetValue(NewProp_MaxPlayers, TEXT("ToolTip"), TEXT("Maximum number of players that can be connected simultaneously to the game session."));
#endif
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FGameLiftGameSessionConfig_CRC() { return 115978913U; }
class UScriptStruct* FGameLiftGameSessionServerProperties::StaticStruct()
{
	extern GAMELIFTCLIENTSDK_API class UPackage* Z_Construct_UPackage__Script_GameLiftClientSDK();
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern GAMELIFTCLIENTSDK_API class UScriptStruct* Z_Construct_UScriptStruct_FGameLiftGameSessionServerProperties();
		extern GAMELIFTCLIENTSDK_API uint32 Get_Z_Construct_UScriptStruct_FGameLiftGameSessionServerProperties_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FGameLiftGameSessionServerProperties, Z_Construct_UPackage__Script_GameLiftClientSDK(), TEXT("GameLiftGameSessionServerProperties"), sizeof(FGameLiftGameSessionServerProperties), Get_Z_Construct_UScriptStruct_FGameLiftGameSessionServerProperties_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FGameLiftGameSessionServerProperties(FGameLiftGameSessionServerProperties::StaticStruct, TEXT("/Script/GameLiftClientSDK"), TEXT("GameLiftGameSessionServerProperties"), false, nullptr, nullptr);
static struct FScriptStruct_GameLiftClientSDK_StaticRegisterNativesFGameLiftGameSessionServerProperties
{
	FScriptStruct_GameLiftClientSDK_StaticRegisterNativesFGameLiftGameSessionServerProperties()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("GameLiftGameSessionServerProperties")),new UScriptStruct::TCppStructOps<FGameLiftGameSessionServerProperties>);
	}
} ScriptStruct_GameLiftClientSDK_StaticRegisterNativesFGameLiftGameSessionServerProperties;
	UScriptStruct* Z_Construct_UScriptStruct_FGameLiftGameSessionServerProperties()
	{
		UPackage* Outer = Z_Construct_UPackage__Script_GameLiftClientSDK();
		extern uint32 Get_Z_Construct_UScriptStruct_FGameLiftGameSessionServerProperties_CRC();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("GameLiftGameSessionServerProperties"), sizeof(FGameLiftGameSessionServerProperties), Get_Z_Construct_UScriptStruct_FGameLiftGameSessionServerProperties_CRC(), false);
		if (!ReturnStruct)
		{
			ReturnStruct = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GameLiftGameSessionServerProperties"), RF_Public|RF_Transient|RF_MarkAsNative) UScriptStruct(FObjectInitializer(), NULL, new UScriptStruct::TCppStructOps<FGameLiftGameSessionServerProperties>, EStructFlags(0x00000001));
			UProperty* NewProp_Value = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Value"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(Value, FGameLiftGameSessionServerProperties), 0x0010000000000004);
			UProperty* NewProp_Key = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Key"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(Key, FGameLiftGameSessionServerProperties), 0x0010000000000004);
			ReturnStruct->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnStruct->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnStruct, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("IsBlueprintBase"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientTypes.h"));
			MetaData->SetValue(NewProp_Value, TEXT("Category"), TEXT("GameLiftGameSessionServerProperties"));
			MetaData->SetValue(NewProp_Value, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientTypes.h"));
			MetaData->SetValue(NewProp_Key, TEXT("Category"), TEXT("GameLiftGameSessionServerProperties"));
			MetaData->SetValue(NewProp_Key, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientTypes.h"));
#endif
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FGameLiftGameSessionServerProperties_CRC() { return 984442782U; }
	void UGameLiftClientObject::StaticRegisterNativesUGameLiftClientObject()
	{
		UClass* Class = UGameLiftClientObject::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "CreateGameLiftObject", (Native)&UGameLiftClientObject::execCreateGameLiftObject },
			{ "CreateGameSession", (Native)&UGameLiftClientObject::execCreateGameSession },
			{ "CreatePlayerSession", (Native)&UGameLiftClientObject::execCreatePlayerSession },
			{ "DescribeGameSession", (Native)&UGameLiftClientObject::execDescribeGameSession },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, 4);
	}
	UFunction* Z_Construct_UFunction_UGameLiftClientObject_CreateGameLiftObject()
	{
		struct GameLiftClientObject_eventCreateGameLiftObject_Parms
		{
			FString AccessKey;
			FString Secret;
			FString Region;
			bool bUsingGameLiftLocal;
			int32 LocalPort;
			UGameLiftClientObject* ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UGameLiftClientObject();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("CreateGameLiftObject"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04022401, 65535, sizeof(GameLiftClientObject_eventCreateGameLiftObject_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(ReturnValue, GameLiftClientObject_eventCreateGameLiftObject_Parms), 0x0010000000000580, Z_Construct_UClass_UGameLiftClientObject_NoRegister());
			UProperty* NewProp_LocalPort = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("LocalPort"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(LocalPort, GameLiftClientObject_eventCreateGameLiftObject_Parms), 0x0010000000000080);
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(bUsingGameLiftLocal, GameLiftClientObject_eventCreateGameLiftObject_Parms, bool);
			UProperty* NewProp_bUsingGameLiftLocal = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("bUsingGameLiftLocal"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(bUsingGameLiftLocal, GameLiftClientObject_eventCreateGameLiftObject_Parms), 0x0010000000000080, CPP_BOOL_PROPERTY_BITMASK(bUsingGameLiftLocal, GameLiftClientObject_eventCreateGameLiftObject_Parms), sizeof(bool), true);
			UProperty* NewProp_Region = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("Region"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(Region, GameLiftClientObject_eventCreateGameLiftObject_Parms), 0x0010000000000080);
			UProperty* NewProp_Secret = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("Secret"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(Secret, GameLiftClientObject_eventCreateGameLiftObject_Parms), 0x0010000000000080);
			UProperty* NewProp_AccessKey = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("AccessKey"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(AccessKey, GameLiftClientObject_eventCreateGameLiftObject_Parms), 0x0010000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("GameLift Client Object"));
			MetaData->SetValue(ReturnFunction, TEXT("CPP_Default_bUsingGameLiftLocal"), TEXT("false"));
			MetaData->SetValue(ReturnFunction, TEXT("CPP_Default_LocalPort"), TEXT("9080"));
			MetaData->SetValue(ReturnFunction, TEXT("CPP_Default_Region"), TEXT("us-east-1"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientObject.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("public static UGameLiftClientObject::CreateGameLiftObject\nCreates a GameLiftClientObject. This function must be called first before accessing any GameLift client functions.\n@param AccessKey [const FString&] AccessKey of your AWS user. @See http://docs.aws.amazon.com/general/latest/gr/managing-aws-access-keys.html\n@param Secret [const FString&] SecretKey of your AWS user. @See http://docs.aws.amazon.com/general/latest/gr/managing-aws-access-keys.html\n@param Region [const FString&] Default is set to us-east-1 (North Virginia).\n@param bUsingGameLiftLocal [bool] If true, then it is assumed you are using GameLift Local. @See http://docs.aws.amazon.com/gamelift/latest/developerguide/integration-testing-local.html#integration-testing-local-server\n@param LocalPort [int32] port to use if bUsingGameLiftLocal is true.\n@return [UGameLiftClientObject*] Returns UGameLiftClientObject*. Use this to create game sessions, player sessions etc."));
			MetaData->SetValue(NewProp_Region, TEXT("NativeConst"), TEXT(""));
			MetaData->SetValue(NewProp_Secret, TEXT("NativeConst"), TEXT(""));
			MetaData->SetValue(NewProp_AccessKey, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UGameLiftClientObject_CreateGameSession()
	{
		struct GameLiftClientObject_eventCreateGameSession_Parms
		{
			FGameLiftGameSessionConfig GameSessionProperties;
			UGameLiftCreateGameSession* ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UGameLiftClientObject();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("CreateGameSession"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04020401, 65535, sizeof(GameLiftClientObject_eventCreateGameSession_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(ReturnValue, GameLiftClientObject_eventCreateGameSession_Parms), 0x0010000000000580, Z_Construct_UClass_UGameLiftCreateGameSession_NoRegister());
			UProperty* NewProp_GameSessionProperties = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("GameSessionProperties"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(GameSessionProperties, GameLiftClientObject_eventCreateGameSession_Parms), 0x0010000000000080, Z_Construct_UScriptStruct_FGameLiftGameSessionConfig());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("GameLift Client Object"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientObject.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("public UGameLiftClientObject::CreateGameSession\nCreates a multi player game session for players.\nThis action creates a game session record and assigns an available server process in the specified fleet to host the game session.\nA fleet must have an ACTIVE status before a game session can be created in it.\nFrom the return value first bind both success and fail events and then call Activate to create game session.\n@param GameSessionProperties [FGameLiftGameSessionConfig] Settings for the game session you want to create.\n@return [UGameLiftCreateGameSession*] Returns UGameLiftCreateGameSession* Object."));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UGameLiftClientObject_CreatePlayerSession()
	{
		struct GameLiftClientObject_eventCreatePlayerSession_Parms
		{
			FString GameSessionID;
			FString UniquePlayerID;
			UGameLiftCreatePlayerSession* ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UGameLiftClientObject();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("CreatePlayerSession"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04020401, 65535, sizeof(GameLiftClientObject_eventCreatePlayerSession_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(ReturnValue, GameLiftClientObject_eventCreatePlayerSession_Parms), 0x0010000000000580, Z_Construct_UClass_UGameLiftCreatePlayerSession_NoRegister());
			UProperty* NewProp_UniquePlayerID = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("UniquePlayerID"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(UniquePlayerID, GameLiftClientObject_eventCreatePlayerSession_Parms), 0x0010000000000080);
			UProperty* NewProp_GameSessionID = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("GameSessionID"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(GameSessionID, GameLiftClientObject_eventCreatePlayerSession_Parms), 0x0010000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("GameLift Client Object"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientObject.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("public UGameLiftClientObject::CreatePlayerSession\nAdds a player to a game session and creates a player session record.\nBefore a player can be added, a game session must have an ACTIVE status, have a creation policy of ALLOW_ALL, and have an open player slot.\nFrom the return value first bind both success and fail events and then call Activate to create player session.\n@param GameSessionID [FString] Unique identifier for the game session to add a player to.\n@param UniquePlayerID [FString] Unique identifier for a player. Player IDs are developer-defined.\n@return [UGameLiftCreatePlayerSession*] Returns UGameLiftCreatePlayerSession* Object."));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UGameLiftClientObject_DescribeGameSession()
	{
		struct GameLiftClientObject_eventDescribeGameSession_Parms
		{
			FString GameSessionID;
			UGameLiftDescribeGameSession* ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UGameLiftClientObject();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("DescribeGameSession"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04020401, 65535, sizeof(GameLiftClientObject_eventDescribeGameSession_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(ReturnValue, GameLiftClientObject_eventDescribeGameSession_Parms), 0x0010000000000580, Z_Construct_UClass_UGameLiftDescribeGameSession_NoRegister());
			UProperty* NewProp_GameSessionID = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("GameSessionID"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(GameSessionID, GameLiftClientObject_eventDescribeGameSession_Parms), 0x0010000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("GameLift Client Object"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientObject.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("public UGameLiftClientObject::DescribeGameSession\nRetrieves the given game session.\nFrom the return value first bind both success and fail events and then call Activate to describe game session.\n@param GameSessionID [FString] Game Session ID. This can be obtained after a successful create game session.\n@return [UGameLiftDescribeGameSession*] Returns UGameLiftDescribeGameSession* Object."));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UGameLiftClientObject_NoRegister()
	{
		return UGameLiftClientObject::StaticClass();
	}
	UClass* Z_Construct_UClass_UGameLiftClientObject()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UObject();
			Z_Construct_UPackage__Script_GameLiftClientSDK();
			OuterClass = UGameLiftClientObject::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20100080;

				OuterClass->LinkChild(Z_Construct_UFunction_UGameLiftClientObject_CreateGameLiftObject());
				OuterClass->LinkChild(Z_Construct_UFunction_UGameLiftClientObject_CreateGameSession());
				OuterClass->LinkChild(Z_Construct_UFunction_UGameLiftClientObject_CreatePlayerSession());
				OuterClass->LinkChild(Z_Construct_UFunction_UGameLiftClientObject_DescribeGameSession());

				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UGameLiftClientObject_CreateGameLiftObject(), "CreateGameLiftObject"); // 942178910
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UGameLiftClientObject_CreateGameSession(), "CreateGameSession"); // 1431000503
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UGameLiftClientObject_CreatePlayerSession(), "CreatePlayerSession"); // 3945569087
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UGameLiftClientObject_DescribeGameSession(), "DescribeGameSession"); // 745934941
				static TCppClassTypeInfo<TCppClassTypeTraits<UGameLiftClientObject> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("BlueprintType"), TEXT("true"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("GameLiftClientObject.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientObject.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGameLiftClientObject, 3774029456);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGameLiftClientObject(Z_Construct_UClass_UGameLiftClientObject, &UGameLiftClientObject::StaticClass, TEXT("/Script/GameLiftClientSDK"), TEXT("UGameLiftClientObject"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameLiftClientObject);
	UFunction* Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreatePlayerSessionFailed__DelegateSignature()
	{
		struct _Script_GameLiftClientSDK_eventOnCreatePlayerSessionFailed_Parms
		{
			FString ErrorMessage;
		};
		UObject* Outer=Z_Construct_UPackage__Script_GameLiftClientSDK();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("OnCreatePlayerSessionFailed__DelegateSignature"), RF_Public|RF_Transient|RF_MarkAsNative) UDelegateFunction(FObjectInitializer(), NULL, 0x00130000, 65535, sizeof(_Script_GameLiftClientSDK_eventOnCreatePlayerSessionFailed_Parms));
			UProperty* NewProp_ErrorMessage = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ErrorMessage"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(ErrorMessage, _Script_GameLiftClientSDK_eventOnCreatePlayerSessionFailed_Parms), 0x0010000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
			MetaData->SetValue(NewProp_ErrorMessage, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreatePlayerSessionSuccess__DelegateSignature()
	{
		struct _Script_GameLiftClientSDK_eventOnCreatePlayerSessionSuccess_Parms
		{
			FString IPAddress;
			FString Port;
			FString PlayerSessionID;
		};
		UObject* Outer=Z_Construct_UPackage__Script_GameLiftClientSDK();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("OnCreatePlayerSessionSuccess__DelegateSignature"), RF_Public|RF_Transient|RF_MarkAsNative) UDelegateFunction(FObjectInitializer(), NULL, 0x00130000, 65535, sizeof(_Script_GameLiftClientSDK_eventOnCreatePlayerSessionSuccess_Parms));
			UProperty* NewProp_PlayerSessionID = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("PlayerSessionID"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(PlayerSessionID, _Script_GameLiftClientSDK_eventOnCreatePlayerSessionSuccess_Parms), 0x0010000000000080);
			UProperty* NewProp_Port = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("Port"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(Port, _Script_GameLiftClientSDK_eventOnCreatePlayerSessionSuccess_Parms), 0x0010000000000080);
			UProperty* NewProp_IPAddress = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("IPAddress"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(IPAddress, _Script_GameLiftClientSDK_eventOnCreatePlayerSessionSuccess_Parms), 0x0010000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
			MetaData->SetValue(NewProp_PlayerSessionID, TEXT("NativeConst"), TEXT(""));
			MetaData->SetValue(NewProp_Port, TEXT("NativeConst"), TEXT(""));
			MetaData->SetValue(NewProp_IPAddress, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UDelegateFunction_GameLiftClientSDK_OnDescribeGameSessionStateFailed__DelegateSignature()
	{
		struct _Script_GameLiftClientSDK_eventOnDescribeGameSessionStateFailed_Parms
		{
			FString ErrorMessage;
		};
		UObject* Outer=Z_Construct_UPackage__Script_GameLiftClientSDK();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("OnDescribeGameSessionStateFailed__DelegateSignature"), RF_Public|RF_Transient|RF_MarkAsNative) UDelegateFunction(FObjectInitializer(), NULL, 0x00130000, 65535, sizeof(_Script_GameLiftClientSDK_eventOnDescribeGameSessionStateFailed_Parms));
			UProperty* NewProp_ErrorMessage = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ErrorMessage"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(ErrorMessage, _Script_GameLiftClientSDK_eventOnDescribeGameSessionStateFailed_Parms), 0x0010000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
			MetaData->SetValue(NewProp_ErrorMessage, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UDelegateFunction_GameLiftClientSDK_OnDescribeGameSessionStateSuccess__DelegateSignature()
	{
		struct _Script_GameLiftClientSDK_eventOnDescribeGameSessionStateSuccess_Parms
		{
			FString SessionID;
			EGameLiftGameSessionStatus SessionState;
		};
		UObject* Outer=Z_Construct_UPackage__Script_GameLiftClientSDK();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("OnDescribeGameSessionStateSuccess__DelegateSignature"), RF_Public|RF_Transient|RF_MarkAsNative) UDelegateFunction(FObjectInitializer(), NULL, 0x00130000, 65535, sizeof(_Script_GameLiftClientSDK_eventOnDescribeGameSessionStateSuccess_Parms));
			UProperty* NewProp_SessionState = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("SessionState"), RF_Public|RF_Transient|RF_MarkAsNative) UEnumProperty(CPP_PROPERTY_BASE(SessionState, _Script_GameLiftClientSDK_eventOnDescribeGameSessionStateSuccess_Parms), 0x0010000000000080, Z_Construct_UEnum_GameLiftClientSDK_EGameLiftGameSessionStatus());
			UProperty* NewProp_SessionState_Underlying = new(EC_InternalUseOnlyConstructor, NewProp_SessionState, TEXT("UnderlyingType"), RF_Public|RF_Transient|RF_MarkAsNative) UByteProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000);
			UProperty* NewProp_SessionID = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("SessionID"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(SessionID, _Script_GameLiftClientSDK_eventOnDescribeGameSessionStateSuccess_Parms), 0x0010000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
			MetaData->SetValue(NewProp_SessionID, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreateGameSessionFailed__DelegateSignature()
	{
		struct _Script_GameLiftClientSDK_eventOnCreateGameSessionFailed_Parms
		{
			FString ErrorMessage;
		};
		UObject* Outer=Z_Construct_UPackage__Script_GameLiftClientSDK();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("OnCreateGameSessionFailed__DelegateSignature"), RF_Public|RF_Transient|RF_MarkAsNative) UDelegateFunction(FObjectInitializer(), NULL, 0x00130000, 65535, sizeof(_Script_GameLiftClientSDK_eventOnCreateGameSessionFailed_Parms));
			UProperty* NewProp_ErrorMessage = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ErrorMessage"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(ErrorMessage, _Script_GameLiftClientSDK_eventOnCreateGameSessionFailed_Parms), 0x0010000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
			MetaData->SetValue(NewProp_ErrorMessage, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreateGameSessionSuccess__DelegateSignature()
	{
		struct _Script_GameLiftClientSDK_eventOnCreateGameSessionSuccess_Parms
		{
			FString GameSessionID;
		};
		UObject* Outer=Z_Construct_UPackage__Script_GameLiftClientSDK();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("OnCreateGameSessionSuccess__DelegateSignature"), RF_Public|RF_Transient|RF_MarkAsNative) UDelegateFunction(FObjectInitializer(), NULL, 0x00130000, 65535, sizeof(_Script_GameLiftClientSDK_eventOnCreateGameSessionSuccess_Parms));
			UProperty* NewProp_GameSessionID = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("GameSessionID"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(GameSessionID, _Script_GameLiftClientSDK_eventOnCreateGameSessionSuccess_Parms), 0x0010000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
			MetaData->SetValue(NewProp_GameSessionID, TEXT("NativeConst"), TEXT(""));
#endif
		}
		return ReturnFunction;
	}
static UEnum* EActivateStatus_StaticEnum()
{
	extern GAMELIFTCLIENTSDK_API class UPackage* Z_Construct_UPackage__Script_GameLiftClientSDK();
	static UEnum* Singleton = nullptr;
	if (!Singleton)
	{
		extern GAMELIFTCLIENTSDK_API class UEnum* Z_Construct_UEnum_GameLiftClientSDK_EActivateStatus();
		Singleton = GetStaticEnum(Z_Construct_UEnum_GameLiftClientSDK_EActivateStatus, Z_Construct_UPackage__Script_GameLiftClientSDK(), TEXT("EActivateStatus"));
	}
	return Singleton;
}
static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EActivateStatus(EActivateStatus_StaticEnum, TEXT("/Script/GameLiftClientSDK"), TEXT("EActivateStatus"), false, nullptr, nullptr);
	UEnum* Z_Construct_UEnum_GameLiftClientSDK_EActivateStatus()
	{
		UPackage* Outer=Z_Construct_UPackage__Script_GameLiftClientSDK();
		extern uint32 Get_Z_Construct_UEnum_GameLiftClientSDK_EActivateStatus_CRC();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EActivateStatus"), 0, Get_Z_Construct_UEnum_GameLiftClientSDK_EActivateStatus_CRC(), false);
		if (!ReturnEnum)
		{
			ReturnEnum = new(EC_InternalUseOnlyConstructor, Outer, TEXT("EActivateStatus"), RF_Public|RF_Transient|RF_MarkAsNative) UEnum(FObjectInitializer());
			TArray<TPair<FName, int64>> EnumNames;
			EnumNames.Emplace(TEXT("EActivateStatus::ACTIVATE_Success"), 0);
			EnumNames.Emplace(TEXT("EActivateStatus::ACTIVATE_NoGameLift"), 1);
			EnumNames.Emplace(TEXT("EActivateStatus::ACTIVATE_NoSuccessCallback"), 2);
			EnumNames.Emplace(TEXT("EActivateStatus::ACTIVATE_NoFailCallback"), 3);
			EnumNames.Emplace(TEXT("EActivateStatus::ACTIVATE_MAX"), 4);
			ReturnEnum->SetEnums(EnumNames, UEnum::ECppForm::EnumClass);
			ReturnEnum->CppType = TEXT("EActivateStatus");
#if WITH_METADATA
			UMetaData* MetaData = ReturnEnum->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnEnum, TEXT("ACTIVATE_NoFailCallback.DisplayName"), TEXT("Failed Delegate not bound"));
			MetaData->SetValue(ReturnEnum, TEXT("ACTIVATE_NoFailCallback.ToolTip"), TEXT("Delegate that was suppose to call when outcome is a failure was not binded to any function."));
			MetaData->SetValue(ReturnEnum, TEXT("ACTIVATE_NoGameLift.DisplayName"), TEXT("Null GameLift"));
			MetaData->SetValue(ReturnEnum, TEXT("ACTIVATE_NoGameLift.ToolTip"), TEXT("GameLiftClient was null. Make sure you called CreateGameLiftObject function."));
			MetaData->SetValue(ReturnEnum, TEXT("ACTIVATE_NoSuccessCallback.DisplayName"), TEXT("Success Delegate not bound"));
			MetaData->SetValue(ReturnEnum, TEXT("ACTIVATE_NoSuccessCallback.ToolTip"), TEXT("Delegate that was suppose to call when outcome is a success was not binded to any function."));
			MetaData->SetValue(ReturnEnum, TEXT("ACTIVATE_Success.DisplayName"), TEXT("Success"));
			MetaData->SetValue(ReturnEnum, TEXT("ACTIVATE_Success.ToolTip"), TEXT("Successfully activated."));
			MetaData->SetValue(ReturnEnum, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnEnum, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
#endif
		}
		return ReturnEnum;
	}
	uint32 Get_Z_Construct_UEnum_GameLiftClientSDK_EActivateStatus_CRC() { return 56441053U; }
	void UGameLiftCreateGameSession::StaticRegisterNativesUGameLiftCreateGameSession()
	{
		UClass* Class = UGameLiftCreateGameSession::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "Activate", (Native)&UGameLiftCreateGameSession::execActivate },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, 1);
	}
	UFunction* Z_Construct_UFunction_UGameLiftCreateGameSession_Activate()
	{
		struct GameLiftCreateGameSession_eventActivate_Parms
		{
			EActivateStatus ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UGameLiftCreateGameSession();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("Activate"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04020401, 65535, sizeof(GameLiftCreateGameSession_eventActivate_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UEnumProperty(CPP_PROPERTY_BASE(ReturnValue, GameLiftCreateGameSession_eventActivate_Parms), 0x0010000000000580, Z_Construct_UEnum_GameLiftClientSDK_EActivateStatus());
			UProperty* NewProp_ReturnValue_Underlying = new(EC_InternalUseOnlyConstructor, NewProp_ReturnValue, TEXT("UnderlyingType"), RF_Public|RF_Transient|RF_MarkAsNative) UByteProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("GameLift CreateGameSession"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UGameLiftCreateGameSession_NoRegister()
	{
		return UGameLiftCreateGameSession::StaticClass();
	}
	UClass* Z_Construct_UClass_UGameLiftCreateGameSession()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UObject();
			Z_Construct_UPackage__Script_GameLiftClientSDK();
			OuterClass = UGameLiftCreateGameSession::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20900080;

				OuterClass->LinkChild(Z_Construct_UFunction_UGameLiftCreateGameSession_Activate());

PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_OnCreateGameSessionFailed = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("OnCreateGameSessionFailed"), RF_Public|RF_Transient|RF_MarkAsNative) UMulticastDelegateProperty(CPP_PROPERTY_BASE(OnCreateGameSessionFailed, UGameLiftCreateGameSession), 0x0010000010080000, Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreateGameSessionFailed__DelegateSignature());
				UProperty* NewProp_OnCreateGameSessionSuccess = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("OnCreateGameSessionSuccess"), RF_Public|RF_Transient|RF_MarkAsNative) UMulticastDelegateProperty(CPP_PROPERTY_BASE(OnCreateGameSessionSuccess, UGameLiftCreateGameSession), 0x0010000010080000, Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreateGameSessionSuccess__DelegateSignature());
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UGameLiftCreateGameSession_Activate(), "Activate"); // 3648664326
				static TCppClassTypeInfo<TCppClassTypeTraits<UGameLiftCreateGameSession> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("GameLiftClientApi.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
				MetaData->SetValue(NewProp_OnCreateGameSessionFailed, TEXT("Category"), TEXT("GameLift CreateGameSession"));
				MetaData->SetValue(NewProp_OnCreateGameSessionFailed, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
				MetaData->SetValue(NewProp_OnCreateGameSessionSuccess, TEXT("Category"), TEXT("GameLift CreateGameSession"));
				MetaData->SetValue(NewProp_OnCreateGameSessionSuccess, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGameLiftCreateGameSession, 78997278);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGameLiftCreateGameSession(Z_Construct_UClass_UGameLiftCreateGameSession, &UGameLiftCreateGameSession::StaticClass, TEXT("/Script/GameLiftClientSDK"), TEXT("UGameLiftCreateGameSession"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameLiftCreateGameSession);
	void UGameLiftDescribeGameSession::StaticRegisterNativesUGameLiftDescribeGameSession()
	{
		UClass* Class = UGameLiftDescribeGameSession::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "Activate", (Native)&UGameLiftDescribeGameSession::execActivate },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, 1);
	}
	UFunction* Z_Construct_UFunction_UGameLiftDescribeGameSession_Activate()
	{
		struct GameLiftDescribeGameSession_eventActivate_Parms
		{
			EActivateStatus ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UGameLiftDescribeGameSession();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("Activate"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04020401, 65535, sizeof(GameLiftDescribeGameSession_eventActivate_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UEnumProperty(CPP_PROPERTY_BASE(ReturnValue, GameLiftDescribeGameSession_eventActivate_Parms), 0x0010000000000580, Z_Construct_UEnum_GameLiftClientSDK_EActivateStatus());
			UProperty* NewProp_ReturnValue_Underlying = new(EC_InternalUseOnlyConstructor, NewProp_ReturnValue, TEXT("UnderlyingType"), RF_Public|RF_Transient|RF_MarkAsNative) UByteProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("GameLift DescribeGameSession"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UGameLiftDescribeGameSession_NoRegister()
	{
		return UGameLiftDescribeGameSession::StaticClass();
	}
	UClass* Z_Construct_UClass_UGameLiftDescribeGameSession()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UObject();
			Z_Construct_UPackage__Script_GameLiftClientSDK();
			OuterClass = UGameLiftDescribeGameSession::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20900080;

				OuterClass->LinkChild(Z_Construct_UFunction_UGameLiftDescribeGameSession_Activate());

PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_OnDescribeGameSessionStateFailed = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("OnDescribeGameSessionStateFailed"), RF_Public|RF_Transient|RF_MarkAsNative) UMulticastDelegateProperty(CPP_PROPERTY_BASE(OnDescribeGameSessionStateFailed, UGameLiftDescribeGameSession), 0x0010000010080000, Z_Construct_UDelegateFunction_GameLiftClientSDK_OnDescribeGameSessionStateFailed__DelegateSignature());
				UProperty* NewProp_OnDescribeGameSessionStateSuccess = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("OnDescribeGameSessionStateSuccess"), RF_Public|RF_Transient|RF_MarkAsNative) UMulticastDelegateProperty(CPP_PROPERTY_BASE(OnDescribeGameSessionStateSuccess, UGameLiftDescribeGameSession), 0x0010000010080000, Z_Construct_UDelegateFunction_GameLiftClientSDK_OnDescribeGameSessionStateSuccess__DelegateSignature());
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UGameLiftDescribeGameSession_Activate(), "Activate"); // 3122377403
				static TCppClassTypeInfo<TCppClassTypeTraits<UGameLiftDescribeGameSession> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("GameLiftClientApi.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
				MetaData->SetValue(NewProp_OnDescribeGameSessionStateFailed, TEXT("Category"), TEXT("GameLift DescribeGameSession"));
				MetaData->SetValue(NewProp_OnDescribeGameSessionStateFailed, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
				MetaData->SetValue(NewProp_OnDescribeGameSessionStateSuccess, TEXT("Category"), TEXT("GameLift DescribeGameSession"));
				MetaData->SetValue(NewProp_OnDescribeGameSessionStateSuccess, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGameLiftDescribeGameSession, 180546286);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGameLiftDescribeGameSession(Z_Construct_UClass_UGameLiftDescribeGameSession, &UGameLiftDescribeGameSession::StaticClass, TEXT("/Script/GameLiftClientSDK"), TEXT("UGameLiftDescribeGameSession"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameLiftDescribeGameSession);
	void UGameLiftCreatePlayerSession::StaticRegisterNativesUGameLiftCreatePlayerSession()
	{
		UClass* Class = UGameLiftCreatePlayerSession::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "Activate", (Native)&UGameLiftCreatePlayerSession::execActivate },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, 1);
	}
	UFunction* Z_Construct_UFunction_UGameLiftCreatePlayerSession_Activate()
	{
		struct GameLiftCreatePlayerSession_eventActivate_Parms
		{
			EActivateStatus ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_UGameLiftCreatePlayerSession();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("Activate"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04020401, 65535, sizeof(GameLiftCreatePlayerSession_eventActivate_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UEnumProperty(CPP_PROPERTY_BASE(ReturnValue, GameLiftCreatePlayerSession_eventActivate_Parms), 0x0010000000000580, Z_Construct_UEnum_GameLiftClientSDK_EActivateStatus());
			UProperty* NewProp_ReturnValue_Underlying = new(EC_InternalUseOnlyConstructor, NewProp_ReturnValue, TEXT("UnderlyingType"), RF_Public|RF_Transient|RF_MarkAsNative) UByteProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("GameLift CreatePlayerSession"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UGameLiftCreatePlayerSession_NoRegister()
	{
		return UGameLiftCreatePlayerSession::StaticClass();
	}
	UClass* Z_Construct_UClass_UGameLiftCreatePlayerSession()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UObject();
			Z_Construct_UPackage__Script_GameLiftClientSDK();
			OuterClass = UGameLiftCreatePlayerSession::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20900080;

				OuterClass->LinkChild(Z_Construct_UFunction_UGameLiftCreatePlayerSession_Activate());

PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_OnCreatePlayerSessionFailed = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("OnCreatePlayerSessionFailed"), RF_Public|RF_Transient|RF_MarkAsNative) UMulticastDelegateProperty(CPP_PROPERTY_BASE(OnCreatePlayerSessionFailed, UGameLiftCreatePlayerSession), 0x0010000010080000, Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreatePlayerSessionFailed__DelegateSignature());
				UProperty* NewProp_OnCreatePlayerSessionSuccess = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("OnCreatePlayerSessionSuccess"), RF_Public|RF_Transient|RF_MarkAsNative) UMulticastDelegateProperty(CPP_PROPERTY_BASE(OnCreatePlayerSessionSuccess, UGameLiftCreatePlayerSession), 0x0010000010080000, Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreatePlayerSessionSuccess__DelegateSignature());
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UGameLiftCreatePlayerSession_Activate(), "Activate"); // 1046195302
				static TCppClassTypeInfo<TCppClassTypeTraits<UGameLiftCreatePlayerSession> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("GameLiftClientApi.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
				MetaData->SetValue(NewProp_OnCreatePlayerSessionFailed, TEXT("Category"), TEXT("GameLift CreatePlayerSession"));
				MetaData->SetValue(NewProp_OnCreatePlayerSessionFailed, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
				MetaData->SetValue(NewProp_OnCreatePlayerSessionSuccess, TEXT("Category"), TEXT("GameLift CreatePlayerSession"));
				MetaData->SetValue(NewProp_OnCreatePlayerSessionSuccess, TEXT("ModuleRelativePath"), TEXT("Public/GameLiftClientApi.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGameLiftCreatePlayerSession, 3580019698);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGameLiftCreatePlayerSession(Z_Construct_UClass_UGameLiftCreatePlayerSession, &UGameLiftCreatePlayerSession::StaticClass, TEXT("/Script/GameLiftClientSDK"), TEXT("UGameLiftCreatePlayerSession"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameLiftCreatePlayerSession);
	UPackage* Z_Construct_UPackage__Script_GameLiftClientSDK()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), nullptr, FName(TEXT("/Script/GameLiftClientSDK")), false, false));
			ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);
			FGuid Guid;
			Guid.A = 0xD6AEC178;
			Guid.B = 0xF9018BC3;
			Guid.C = 0x00000000;
			Guid.D = 0x00000000;
			ReturnPackage->SetGuid(Guid);

			Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreateGameSessionSuccess__DelegateSignature();
			Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreateGameSessionFailed__DelegateSignature();
			Z_Construct_UDelegateFunction_GameLiftClientSDK_OnDescribeGameSessionStateSuccess__DelegateSignature();
			Z_Construct_UDelegateFunction_GameLiftClientSDK_OnDescribeGameSessionStateFailed__DelegateSignature();
			Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreatePlayerSessionSuccess__DelegateSignature();
			Z_Construct_UDelegateFunction_GameLiftClientSDK_OnCreatePlayerSessionFailed__DelegateSignature();
		}
		return ReturnPackage;
	}
#endif
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
