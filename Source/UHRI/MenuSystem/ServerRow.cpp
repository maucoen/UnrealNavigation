// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MainMenu.h"

void UServerRow::Setup(class UMainMenu* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;
	RowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
	RowButton->OnHovered.AddDynamic(this, &UServerRow::OnHovered);
	RowButton->OnUnhovered.AddDynamic(this, &UServerRow::OnUnhovered);
}


void UServerRow::OnClicked()
{
	Parent->SelectIndex(Index);
	ServerName->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
	HostUser->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
	ConnectionFraction->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
}
void UServerRow::OnHovered()
{
	if (!Selected)
		ServerName->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
		HostUser->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
		ConnectionFraction->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
}
void UServerRow::OnUnhovered()
{
	if (!Selected)
		ServerName->SetColorAndOpacity(FSlateColor(FLinearColor::White));
		HostUser->SetColorAndOpacity(FSlateColor(FLinearColor::White));
		ConnectionFraction->SetColorAndOpacity(FSlateColor(FLinearColor::White));
}
void UServerRow::ResetColor()
{
	ServerName->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	HostUser->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	ConnectionFraction->SetColorAndOpacity(FSlateColor(FLinearColor::White));

}
