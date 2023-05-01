// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LD53_API UGameOverUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LD53", meta = (AllowPrivateAccess = "true"))
	TArray<FString> Levels;

private:
	int m_NextLevelIndex = 0;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txtGameOver;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txtScore;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* btnContinue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* btnRestart;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* btnQuit;

public:
	void ShowScoreText(FString _Text);
	void HideScoreText();
	void ShowContinueButton(int _NextLevelIndex);
	void HideContinueButton();

	UFUNCTION()
	void OnContinueClicked();
	
	UFUNCTION()
	void OnRestartClicked();

	UFUNCTION()
	void OnQuitClicked();
};
