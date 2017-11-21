// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FVector;
struct FHitResult;
#ifdef UHRI_UHRIProjectile_generated_h
#error "UHRIProjectile.generated.h already included, missing '#pragma once' in UHRIProjectile.h"
#endif
#define UHRI_UHRIProjectile_generated_h

#define UHRI_Source_UHRI_UHRIProjectile_h_12_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define UHRI_Source_UHRI_UHRIProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define UHRI_Source_UHRI_UHRIProjectile_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAUHRIProjectile(); \
	friend UHRI_API class UClass* Z_Construct_UClass_AUHRIProjectile(); \
public: \
	DECLARE_CLASS(AUHRIProjectile, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UHRI"), NO_API) \
	DECLARE_SERIALIZER(AUHRIProjectile) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Source_UHRI_UHRIProjectile_h_12_INCLASS \
private: \
	static void StaticRegisterNativesAUHRIProjectile(); \
	friend UHRI_API class UClass* Z_Construct_UClass_AUHRIProjectile(); \
public: \
	DECLARE_CLASS(AUHRIProjectile, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/UHRI"), NO_API) \
	DECLARE_SERIALIZER(AUHRIProjectile) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UHRI_Source_UHRI_UHRIProjectile_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AUHRIProjectile(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AUHRIProjectile) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AUHRIProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AUHRIProjectile); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AUHRIProjectile(AUHRIProjectile&&); \
	NO_API AUHRIProjectile(const AUHRIProjectile&); \
public:


#define UHRI_Source_UHRI_UHRIProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AUHRIProjectile(AUHRIProjectile&&); \
	NO_API AUHRIProjectile(const AUHRIProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AUHRIProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AUHRIProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AUHRIProjectile)


#define UHRI_Source_UHRI_UHRIProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CollisionComp() { return STRUCT_OFFSET(AUHRIProjectile, CollisionComp); } \
	FORCEINLINE static uint32 __PPO__ProjectileMovement() { return STRUCT_OFFSET(AUHRIProjectile, ProjectileMovement); }


#define UHRI_Source_UHRI_UHRIProjectile_h_9_PROLOG
#define UHRI_Source_UHRI_UHRIProjectile_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Source_UHRI_UHRIProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	UHRI_Source_UHRI_UHRIProjectile_h_12_RPC_WRAPPERS \
	UHRI_Source_UHRI_UHRIProjectile_h_12_INCLASS \
	UHRI_Source_UHRI_UHRIProjectile_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UHRI_Source_UHRI_UHRIProjectile_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UHRI_Source_UHRI_UHRIProjectile_h_12_PRIVATE_PROPERTY_OFFSET \
	UHRI_Source_UHRI_UHRIProjectile_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	UHRI_Source_UHRI_UHRIProjectile_h_12_INCLASS_NO_PURE_DECLS \
	UHRI_Source_UHRI_UHRIProjectile_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID UHRI_Source_UHRI_UHRIProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
