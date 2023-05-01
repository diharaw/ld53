// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDUserWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/TextBlock.h"

void UHUDUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HidePrimaryPrompt();
	HideSecondaryPrompt();
}

void UHUDUserWidget::ShowPrimaryPrompt(FString _Text)
{
	if (blurPrimary)
	{
		blurPrimary->SetVisibility(ESlateVisibility::Visible);

		if (txtPrimary)
			txtPrimary->SetText(FText::FromString(_Text));
	}
}

void UHUDUserWidget::HidePrimaryPrompt()
{
	if (blurPrimary)
		blurPrimary->SetVisibility(ESlateVisibility::Hidden);
}

void UHUDUserWidget::ShowSecondaryPrompt(FString _Text)
{
	if (blurSecondary)
	{
		blurSecondary->SetVisibility(ESlateVisibility::Visible);

		if (txtSecondary)
			txtSecondary->SetText(FText::FromString(_Text));
	}
}

void UHUDUserWidget::HideSecondaryPrompt()
{
	if (blurSecondary)
		blurSecondary->SetVisibility(ESlateVisibility::Hidden);
}

void UHUDUserWidget::UpdatePowerLevelText(FString _Text)
{
	if (txtPowerLevel)
		txtPowerLevel->SetText(FText::FromString(_Text));
}
