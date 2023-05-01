// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UGameOverUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HideScoreText();
	HideContinueButton();

	if (btnContinue)
		btnContinue->OnClicked.AddUniqueDynamic(this, &UGameOverUserWidget::OnContinueClicked);
	
	if (btnRestart)
		btnRestart->OnClicked.AddUniqueDynamic(this, &UGameOverUserWidget::OnRestartClicked);
	
	if (btnQuit)
		btnQuit->OnClicked.AddUniqueDynamic(this, &UGameOverUserWidget::OnQuitClicked);
}

void UGameOverUserWidget::ShowScoreText(FString _Text)
{
	if (txtScore)
	{
		txtScore->SetVisibility(ESlateVisibility::Visible);
		txtScore->SetText(FText::FromString(_Text));
	}
}

void UGameOverUserWidget::HideScoreText()
{
	if (txtScore)
		txtScore->SetVisibility(ESlateVisibility::Hidden);
}

void UGameOverUserWidget::ShowContinueButton(int _NextLevelIndex)
{
	m_NextLevelIndex = _NextLevelIndex;

	if (btnContinue)
		btnContinue->SetVisibility(ESlateVisibility::Visible);
}

void UGameOverUserWidget::HideContinueButton()
{
	if (btnContinue)
		btnContinue->SetVisibility(ESlateVisibility::Hidden);
}

void UGameOverUserWidget::OnContinueClicked()
{
	if (m_NextLevelIndex < Levels.Num())
	{
		GetWorld()->GetFirstPlayerController()->SetPause(false);
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

		UGameplayStatics::OpenLevel(this, FName(*Levels[m_NextLevelIndex]), true);
	}
}

void UGameOverUserWidget::OnRestartClicked()
{
	GetWorld()->GetFirstPlayerController()->SetPause(false);
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

	UGameplayStatics::OpenLevel(this, "LV_Level1", true);
}

void UGameOverUserWidget::OnQuitClicked()
{
	UGameplayStatics::OpenLevel(this, "LV_MainMenu", true);
}