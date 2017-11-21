// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef UHRI_UHRICharacter_generated_h
#error "UHRICharacter.generated.h already included, missing '#pragma once' in UHRICharacter.h"
#endif
#define UHRI_UHRICharacter_generated_h

#define UHRI_Source_UHRI_UHRICharacter_h_14_RPC_WRAPPERS
#define UHRI_Source_UHRI_UHRICharacter_h_14_RPC_WRAPPERS_NO_PURE_DECLS
#define UHRI_Source_UHRI_UHRICharacter_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAUHRICharacter(); \
	friend UHRI_API class UClass* Z_Construct_UClass_AUHRICharacter(); \
public: \
	DECLARE_CLASS(AUHRICharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UHRI"), NO_API) \
	DECLARE_SERIALIZER(AUHRICharacter) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Source_UHRI_UHRICharacter_h_14_INCLASS \
private: \
	static void StaticRegisterNativesAUHRICharacter(); \
	friend UHRI_API class UClass* Z_Construct_UClass_AUHRICharacter(); \
public: \
	DECLARE_CLASS(AUHRICharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UHRI"), NO_API) \
	DECLARE_SERIALIZER(AUHRICharacter) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Source_UHRI_UHRICharacter_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AUHRICharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AUHRICharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AUHRICharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AUHRICharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AUHRICharacter(AUHRICharacter&&); \
	NO_API AUHRICharacter(const AUHRICharacter&); \
public:


#define UHRI_Source_UHRI_UHRICharacter_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AUHRICharacter(AUHRICharacter&&); \
	NO_API AUHRICharacter(const AUHRICharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AUHRICharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AUHRICharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AUHRICharacter)


#define UHRI_Source_UHRI_UHRICharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__Mesh1P() { return STRUCT_OFFSET(AUHRICharacter, Mesh1P); } \
	FORCEINLINE static uint32 __PPO__FP_Gun() { return STRUCT_OFFSET(AUHRICharacter, FP_Gun); } \
	FORCEINLINE static uint32 __PPO__FP_MuzzleLocation() { return STRUCT_OFFSET(AUHRICharacter, FP_MuzzleLocation); } \
	FORCEINLINE static uint32 __PPO__VR_Gun() { return STRUCT_OFFSET(AUHRICharacter, VR_Gun); } \
	FORCEINLINE static uint32 __PPO__VR_MuzzleLocation() { return STRUCT_OFFSET(AUHRICharacter, VR_MuzzleLocation); } \
	FORCEINLINE static uint32 __PPO__FirstPersonCameraComponent() { return STRUCT_OFFSET(AUHRICharacter, FirstPersonCameraComponent); } \
	FORCEINLINE static uint32 __PPO__R_MotionController() { return STRUCT_OFFSET(AUHRICharacter, R_MotionController); } \
	FORCEINLINE static uint32 __PPO__L_MotionController() { return STRUCT_OFFSET(AUHRICharacter, L_MotionController); }


#define UHRI_Source_UHRI_UHRICharacter_h_11_PROLOG
#define UHRI_Source_UHRI_UHRICharacter_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Source_UHRI_UHRICharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	UHRI_Source_UHRI_UHRICharacter_h_14_RPC_WRAPPERS \
	UHRI_Source_UHRI_UHRICharacter_h_14_INCLASS \
	UHRI_Source_UHRI_UHRICharacter_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UHRI_Source_UHRI_UHRICharacter_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Source_UHRI_UHRICharacter_h_14_PRIVATE_PROPERTY_OFFSET \
	UHRI_Source_UHRI_UHRICharacter_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	UHRI_Source_UHRI_UHRICharacter_h_14_INCLASS_NO_PURE_DECLS \
	UHRI_Source_UHRI_UHRICharacter_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID UHRI_Source_UHRI_UHRICharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
