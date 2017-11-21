// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef UHRI_MenuWidget_generated_h
#error "MenuWidget.generated.h already included, missing '#pragma once' in MenuWidget.h"
#endif
#define UHRI_MenuWidget_generated_h

#define UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_RPC_WRAPPERS
#define UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_RPC_WRAPPERS_NO_PURE_DECLS
#define UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMenuWidget(); \
	friend UHRI_API class UClass* Z_Construct_UClass_UMenuWidget(); \
public: \
	DECLARE_CLASS(UMenuWidget, UUserWidget, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UHRI"), NO_API) \
	DECLARE_SERIALIZER(UMenuWidget) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_INCLASS \
private: \
	static void StaticRegisterNativesUMenuWidget(); \
	friend UHRI_API class UClass* Z_Construct_UClass_UMenuWidget(); \
public: \
	DECLARE_CLASS(UMenuWidget, UUserWidget, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UHRI"), NO_API) \
	DECLARE_SERIALIZER(UMenuWidget) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMenuWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMenuWidget) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMenuWidget); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMenuWidget); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMenuWidget(UMenuWidget&&); \
	NO_API UMenuWidget(const UMenuWidget&); \
public:


#define UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMenuWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMenuWidget(UMenuWidget&&); \
	NO_API UMenuWidget(const UMenuWidget&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMenuWidget); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMenuWidget); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMenuWidget)


#define UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_PRIVATE_PROPERTY_OFFSET
#define UHRI_Source_UHRI_MenuSystem_MenuWidget_h_14_PROLOG
#define UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_PRIVATE_PROPERTY_OFFSET \
	UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_RPC_WRAPPERS \
	UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_INCLASS \
	UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_PRIVATE_PROPERTY_OFFSET \
	UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_INCLASS_NO_PURE_DECLS \
	UHRI_Source_UHRI_MenuSystem_MenuWidget_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID UHRI_Source_UHRI_MenuSystem_MenuWidget_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
