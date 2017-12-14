// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EGameLiftGameSessionStatus : uint8;
enum class EActivateStatus : uint8;
#ifdef GAMELIFTCLIENTSDK_GameLiftClientApi_generated_h
#error "GameLiftClientApi.generated.h already included, missing '#pragma once' in GameLiftClientApi.h"
#endif
#define GAMELIFTCLIENTSDK_GameLiftClientApi_generated_h

#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_97_DELEGATE \
struct _Script_GameLiftClientSDK_eventOnCreatePlayerSessionFailed_Parms \
{ \
	FString ErrorMessage; \
}; \
static inline void FOnCreatePlayerSessionFailed_DelegateWrapper(const FMulticastScriptDelegate& OnCreatePlayerSessionFailed, const FString& ErrorMessage) \
{ \
	_Script_GameLiftClientSDK_eventOnCreatePlayerSessionFailed_Parms Parms; \
	Parms.ErrorMessage=ErrorMessage; \
	OnCreatePlayerSessionFailed.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_96_DELEGATE \
struct _Script_GameLiftClientSDK_eventOnCreatePlayerSessionSuccess_Parms \
{ \
	FString IPAddress; \
	FString Port; \
	FString PlayerSessionID; \
}; \
static inline void FOnCreatePlayerSessionSuccess_DelegateWrapper(const FMulticastScriptDelegate& OnCreatePlayerSessionSuccess, const FString& IPAddress, const FString& Port, const FString& PlayerSessionID) \
{ \
	_Script_GameLiftClientSDK_eventOnCreatePlayerSessionSuccess_Parms Parms; \
	Parms.IPAddress=IPAddress; \
	Parms.Port=Port; \
	Parms.PlayerSessionID=PlayerSessionID; \
	OnCreatePlayerSessionSuccess.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_65_DELEGATE \
struct _Script_GameLiftClientSDK_eventOnDescribeGameSessionStateFailed_Parms \
{ \
	FString ErrorMessage; \
}; \
static inline void FOnDescribeGameSessionStateFailed_DelegateWrapper(const FMulticastScriptDelegate& OnDescribeGameSessionStateFailed, const FString& ErrorMessage) \
{ \
	_Script_GameLiftClientSDK_eventOnDescribeGameSessionStateFailed_Parms Parms; \
	Parms.ErrorMessage=ErrorMessage; \
	OnDescribeGameSessionStateFailed.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_64_DELEGATE \
struct _Script_GameLiftClientSDK_eventOnDescribeGameSessionStateSuccess_Parms \
{ \
	FString SessionID; \
	EGameLiftGameSessionStatus SessionState; \
}; \
static inline void FOnDescribeGameSessionStateSuccess_DelegateWrapper(const FMulticastScriptDelegate& OnDescribeGameSessionStateSuccess, const FString& SessionID, EGameLiftGameSessionStatus SessionState) \
{ \
	_Script_GameLiftClientSDK_eventOnDescribeGameSessionStateSuccess_Parms Parms; \
	Parms.SessionID=SessionID; \
	Parms.SessionState=SessionState; \
	OnDescribeGameSessionStateSuccess.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_33_DELEGATE \
struct _Script_GameLiftClientSDK_eventOnCreateGameSessionFailed_Parms \
{ \
	FString ErrorMessage; \
}; \
static inline void FOnCreateGameSessionFailed_DelegateWrapper(const FMulticastScriptDelegate& OnCreateGameSessionFailed, const FString& ErrorMessage) \
{ \
	_Script_GameLiftClientSDK_eventOnCreateGameSessionFailed_Parms Parms; \
	Parms.ErrorMessage=ErrorMessage; \
	OnCreateGameSessionFailed.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_32_DELEGATE \
struct _Script_GameLiftClientSDK_eventOnCreateGameSessionSuccess_Parms \
{ \
	FString GameSessionID; \
}; \
static inline void FOnCreateGameSessionSuccess_DelegateWrapper(const FMulticastScriptDelegate& OnCreateGameSessionSuccess, const FString& GameSessionID) \
{ \
	_Script_GameLiftClientSDK_eventOnCreateGameSessionSuccess_Parms Parms; \
	Parms.GameSessionID=GameSessionID; \
	OnCreateGameSessionSuccess.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execActivate) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(EActivateStatus*)Z_Param__Result=this->Activate(); \
		P_NATIVE_END; \
	}


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execActivate) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(EActivateStatus*)Z_Param__Result=this->Activate(); \
		P_NATIVE_END; \
	}


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameLiftCreateGameSession(); \
	friend GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftCreateGameSession(); \
public: \
	DECLARE_CLASS(UGameLiftCreateGameSession, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/GameLiftClientSDK"), NO_API) \
	DECLARE_SERIALIZER(UGameLiftCreateGameSession) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_INCLASS \
private: \
	static void StaticRegisterNativesUGameLiftCreateGameSession(); \
	friend GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftCreateGameSession(); \
public: \
	DECLARE_CLASS(UGameLiftCreateGameSession, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/GameLiftClientSDK"), NO_API) \
	DECLARE_SERIALIZER(UGameLiftCreateGameSession) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGameLiftCreateGameSession(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameLiftCreateGameSession) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGameLiftCreateGameSession); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameLiftCreateGameSession); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGameLiftCreateGameSession(UGameLiftCreateGameSession&&); \
	NO_API UGameLiftCreateGameSession(const UGameLiftCreateGameSession&); \
public:


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGameLiftCreateGameSession(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGameLiftCreateGameSession(UGameLiftCreateGameSession&&); \
	NO_API UGameLiftCreateGameSession(const UGameLiftCreateGameSession&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGameLiftCreateGameSession); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameLiftCreateGameSession); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameLiftCreateGameSession)


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_PRIVATE_PROPERTY_OFFSET
#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_34_PROLOG
#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_PRIVATE_PROPERTY_OFFSET \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_RPC_WRAPPERS \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_INCLASS \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_PRIVATE_PROPERTY_OFFSET \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_RPC_WRAPPERS_NO_PURE_DECLS \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_INCLASS_NO_PURE_DECLS \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_37_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execActivate) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(EActivateStatus*)Z_Param__Result=this->Activate(); \
		P_NATIVE_END; \
	}


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execActivate) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(EActivateStatus*)Z_Param__Result=this->Activate(); \
		P_NATIVE_END; \
	}


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameLiftDescribeGameSession(); \
	friend GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftDescribeGameSession(); \
public: \
	DECLARE_CLASS(UGameLiftDescribeGameSession, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/GameLiftClientSDK"), NO_API) \
	DECLARE_SERIALIZER(UGameLiftDescribeGameSession) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_INCLASS \
private: \
	static void StaticRegisterNativesUGameLiftDescribeGameSession(); \
	friend GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftDescribeGameSession(); \
public: \
	DECLARE_CLASS(UGameLiftDescribeGameSession, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/GameLiftClientSDK"), NO_API) \
	DECLARE_SERIALIZER(UGameLiftDescribeGameSession) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGameLiftDescribeGameSession(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameLiftDescribeGameSession) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGameLiftDescribeGameSession); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameLiftDescribeGameSession); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGameLiftDescribeGameSession(UGameLiftDescribeGameSession&&); \
	NO_API UGameLiftDescribeGameSession(const UGameLiftDescribeGameSession&); \
public:


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGameLiftDescribeGameSession(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGameLiftDescribeGameSession(UGameLiftDescribeGameSession&&); \
	NO_API UGameLiftDescribeGameSession(const UGameLiftDescribeGameSession&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGameLiftDescribeGameSession); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameLiftDescribeGameSession); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameLiftDescribeGameSession)


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_PRIVATE_PROPERTY_OFFSET
#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_66_PROLOG
#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_PRIVATE_PROPERTY_OFFSET \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_RPC_WRAPPERS \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_INCLASS \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_PRIVATE_PROPERTY_OFFSET \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_RPC_WRAPPERS_NO_PURE_DECLS \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_INCLASS_NO_PURE_DECLS \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_69_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execActivate) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(EActivateStatus*)Z_Param__Result=this->Activate(); \
		P_NATIVE_END; \
	}


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execActivate) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(EActivateStatus*)Z_Param__Result=this->Activate(); \
		P_NATIVE_END; \
	}


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameLiftCreatePlayerSession(); \
	friend GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftCreatePlayerSession(); \
public: \
	DECLARE_CLASS(UGameLiftCreatePlayerSession, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/GameLiftClientSDK"), NO_API) \
	DECLARE_SERIALIZER(UGameLiftCreatePlayerSession) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_INCLASS \
private: \
	static void StaticRegisterNativesUGameLiftCreatePlayerSession(); \
	friend GAMELIFTCLIENTSDK_API class UClass* Z_Construct_UClass_UGameLiftCreatePlayerSession(); \
public: \
	DECLARE_CLASS(UGameLiftCreatePlayerSession, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/GameLiftClientSDK"), NO_API) \
	DECLARE_SERIALIZER(UGameLiftCreatePlayerSession) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGameLiftCreatePlayerSession(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameLiftCreatePlayerSession) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGameLiftCreatePlayerSession); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameLiftCreatePlayerSession); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGameLiftCreatePlayerSession(UGameLiftCreatePlayerSession&&); \
	NO_API UGameLiftCreatePlayerSession(const UGameLiftCreatePlayerSession&); \
public:


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGameLiftCreatePlayerSession(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGameLiftCreatePlayerSession(UGameLiftCreatePlayerSession&&); \
	NO_API UGameLiftCreatePlayerSession(const UGameLiftCreatePlayerSession&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGameLiftCreatePlayerSession); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameLiftCreatePlayerSession); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameLiftCreatePlayerSession)


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_PRIVATE_PROPERTY_OFFSET
#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_98_PROLOG
#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_PRIVATE_PROPERTY_OFFSET \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_RPC_WRAPPERS \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_INCLASS \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_PRIVATE_PROPERTY_OFFSET \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_RPC_WRAPPERS_NO_PURE_DECLS \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_INCLASS_NO_PURE_DECLS \
	UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h_101_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID UHRI_Plugins_GameLiftClientSDK_Source_GameLiftClientSDK_Public_GameLiftClientApi_h


#define FOREACH_ENUM_EACTIVATESTATUS(op) \
	op(EActivateStatus::ACTIVATE_Success) \
	op(EActivateStatus::ACTIVATE_NoGameLift) \
	op(EActivateStatus::ACTIVATE_NoSuccessCallback) \
	op(EActivateStatus::ACTIVATE_NoFailCallback) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
