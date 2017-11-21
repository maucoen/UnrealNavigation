// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

#include "UHRIGameInstance.generated.h"

/**
*
*/
UCLASS()
class UHRI_API UUHRIGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UUHRIGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
		void LoadMenuWidget();

	UFUNCTION(BlueprintCallable)
		void InGameLoadMenu();

	UFUNCTION(Exec)
		void Host(FString ServerName) override;

	UFUNCTION(Exec)
		void Join(uint32 Index) override;

	void StartSession();

	virtual void LoadMainMenu() override;
	virtual void RequestServerList() override;

private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu* Menu;

	IOnlineSessionPtr SessionInterface;

	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionsComplete(bool Success);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);


	FString DesiredServerName;

	void CreateSession();

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

};

