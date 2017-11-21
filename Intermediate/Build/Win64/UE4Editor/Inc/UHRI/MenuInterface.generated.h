// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef UHRI_MenuInterface_generated_h
#error "MenuInterface.generated.h already included, missing '#pragma once' in MenuInterface.h"
#endif
#define UHRI_MenuInterface_generated_h

#define UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_RPC_WRAPPERS
#define UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	UHRI_API UMenuInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMenuInterface) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(UHRI_API, UMenuInterface); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMenuInterface); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UHRI_API UMenuInterface(UMenuInterface&&); \
	UHRI_API UMenuInterface(const UMenuInterface&); \
public:


#define UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	UHRI_API UMenuInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UHRI_API UMenuInterface(UMenuInterface&&); \
	UHRI_API UMenuInterface(const UMenuInterface&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(UHRI_API, UMenuInterface); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMenuInterface); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMenuInterface)


#undef GENERATED_UINTERFACE_BODY_COMMON
#define GENERATED_UINTERFACE_BODY_COMMON() \
private: \
	static void StaticRegisterNativesUMenuInterface(); \
	friend UHRI_API class UClass* Z_Construct_UClass_UMenuInterface(); \
public: \
	DECLARE_CLASS(UMenuInterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), 0, TEXT("/Script/UHRI"), UHRI_API) \
	DECLARE_SERIALIZER(UMenuInterface) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_GENERATED_BODY_LEGACY \
		PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	GENERATED_UINTERFACE_BODY_COMMON() \
	UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_STANDARD_CONSTRUCTORS \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	GENERATED_UINTERFACE_BODY_COMMON() \
	UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IMenuInterface() {} \
public: \
	typedef UMenuInterface UClassType; \
	virtual UObject* _getUObject() const { check(0 && "Missing required implementation."); return nullptr; }


#define UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_INCLASS_IINTERFACE \
protected: \
	virtual ~IMenuInterface() {} \
public: \
	typedef UMenuInterface UClassType; \
	virtual UObject* _getUObject() const { check(0 && "Missing required implementation."); return nullptr; }


#define UHRI_Source_UHRI_MenuSystem_MenuInterface_h_9_PROLOG
#define UHRI_Source_UHRI_MenuSystem_MenuInterface_h_20_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_RPC_WRAPPERS \
	UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_INCLASS_IINTERFACE \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UHRI_Source_UHRI_MenuSystem_MenuInterface_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	UHRI_Source_UHRI_MenuSystem_MenuInterface_h_12_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID UHRI_Source_UHRI_MenuSystem_MenuInterface_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
