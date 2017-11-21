// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef UHRI_UHRIGameInstance_generated_h
#error "UHRIGameInstance.generated.h already included, missing '#pragma once' in UHRIGameInstance.h"
#endif
#define UHRI_UHRIGameInstance_generated_h

#define UHRI_Source_UHRI_UHRIGameInstance_h_19_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execJoin) \
	{ \
		P_GET_PROPERTY(UUInt32Property,Z_Param_Index); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->Join(Z_Param_Index); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execHost) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->Host(Z_Param_ServerName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execInGameLoadMenu) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->InGameLoadMenu(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoadMenuWidget) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->LoadMenuWidget(); \
		P_NATIVE_END; \
	}


#define UHRI_Source_UHRI_UHRIGameInstance_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execJoin) \
	{ \
		P_GET_PROPERTY(UUInt32Property,Z_Param_Index); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->Join(Z_Param_Index); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execHost) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_ServerName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->Host(Z_Param_ServerName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execInGameLoadMenu) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->InGameLoadMenu(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoadMenuWidget) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->LoadMenuWidget(); \
		P_NATIVE_END; \
	}


#define UHRI_Source_UHRI_UHRIGameInstance_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUUHRIGameInstance(); \
	friend UHRI_API class UClass* Z_Construct_UClass_UUHRIGameInstance(); \
public: \
	DECLARE_CLASS(UUHRIGameInstance, UGameInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), 0, TEXT("/Script/UHRI"), NO_API) \
	DECLARE_SERIALIZER(UUHRIGameInstance) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	virtual UObject* _getUObject() const override { return const_cast<UUHRIGameInstance*>(this); }


#define UHRI_Source_UHRI_UHRIGameInstance_h_19_INCLASS \
private: \
	static void StaticRegisterNativesUUHRIGameInstance(); \
	friend UHRI_API class UClass* Z_Construct_UClass_UUHRIGameInstance(); \
public: \
	DECLARE_CLASS(UUHRIGameInstance, UGameInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), 0, TEXT("/Script/UHRI"), NO_API) \
	DECLARE_SERIALIZER(UUHRIGameInstance) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC}; \
	virtual UObject* _getUObject() const override { return const_cast<UUHRIGameInstance*>(this); }


#define UHRI_Source_UHRI_UHRIGameInstance_h_19_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UUHRIGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UUHRIGameInstance) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UUHRIGameInstance); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UUHRIGameInstance); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UUHRIGameInstance(UUHRIGameInstance&&); \
	NO_API UUHRIGameInstance(const UUHRIGameInstance&); \
public:


#define UHRI_Source_UHRI_UHRIGameInstance_h_19_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UUHRIGameInstance(UUHRIGameInstance&&); \
	NO_API UUHRIGameInstance(const UUHRIGameInstance&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UUHRIGameInstance); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UUHRIGameInstance); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UUHRIGameInstance)


#define UHRI_Source_UHRI_UHRIGameInstance_h_19_PRIVATE_PROPERTY_OFFSET
#define UHRI_Source_UHRI_UHRIGameInstance_h_16_PROLOG
#define UHRI_Source_UHRI_UHRIGameInstance_h_19_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Source_UHRI_UHRIGameInstance_h_19_PRIVATE_PROPERTY_OFFSET \
	UHRI_Source_UHRI_UHRIGameInstance_h_19_RPC_WRAPPERS \
	UHRI_Source_UHRI_UHRIGameInstance_h_19_INCLASS \
	UHRI_Source_UHRI_UHRIGameInstance_h_19_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UHRI_Source_UHRI_UHRIGameInstance_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Source_UHRI_UHRIGameInstance_h_19_PRIVATE_PROPERTY_OFFSET \
	UHRI_Source_UHRI_UHRIGameInstance_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	UHRI_Source_UHRI_UHRIGameInstance_h_19_INCLASS_NO_PURE_DECLS \
	UHRI_Source_UHRI_UHRIGameInstance_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID UHRI_Source_UHRI_UHRIGameInstance_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
