// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef UHRI_InGameMenu_generated_h
#error "InGameMenu.generated.h already included, missing '#pragma once' in InGameMenu.h"
#endif
#define UHRI_InGameMenu_generated_h

#define UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execQuitPressed) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->QuitPressed(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCancelPressed) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->CancelPressed(); \
		P_NATIVE_END; \
	}


#define UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execQuitPressed) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->QuitPressed(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCancelPressed) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->CancelPressed(); \
		P_NATIVE_END; \
	}


#define UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUInGameMenu(); \
	friend UHRI_API class UClass* Z_Construct_UClass_UInGameMenu(); \
public: \
	DECLARE_CLASS(UInGameMenu, UMenuWidget, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UHRI"), NO_API) \
	DECLARE_SERIALIZER(UInGameMenu) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_INCLASS \
private: \
	static void StaticRegisterNativesUInGameMenu(); \
	friend UHRI_API class UClass* Z_Construct_UClass_UInGameMenu(); \
public: \
	DECLARE_CLASS(UInGameMenu, UMenuWidget, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UHRI"), NO_API) \
	DECLARE_SERIALIZER(UInGameMenu) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInGameMenu(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInGameMenu) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInGameMenu); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInGameMenu); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UInGameMenu(UInGameMenu&&); \
	NO_API UInGameMenu(const UInGameMenu&); \
public:


#define UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInGameMenu(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UInGameMenu(UInGameMenu&&); \
	NO_API UInGameMenu(const UInGameMenu&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInGameMenu); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInGameMenu); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInGameMenu)


#define UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CancelButton() { return STRUCT_OFFSET(UInGameMenu, CancelButton); } \
	FORCEINLINE static uint32 __PPO__QuitButton() { return STRUCT_OFFSET(UInGameMenu, QuitButton); }


#define UHRI_Source_UHRI_MenuSystem_InGameMenu_h_12_PROLOG
#define UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_PRIVATE_PROPERTY_OFFSET \
	UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_RPC_WRAPPERS \
	UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_INCLASS \
	UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_PRIVATE_PROPERTY_OFFSET \
	UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_INCLASS_NO_PURE_DECLS \
	UHRI_Source_UHRI_MenuSystem_InGameMenu_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID UHRI_Source_UHRI_MenuSystem_InGameMenu_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
