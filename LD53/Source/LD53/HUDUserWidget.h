// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LD53_API UHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* imgCrosshair;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UBackgroundBlur* blurPrimary;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UBackgroundBlur* blurSecondary;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txtPrimary;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txtSecondary;

public:
	UFUNCTION(BlueprintCallable, Category = "LD53")
	void ShowPrimaryPrompt(FString _Text);

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void HidePrimaryPrompt();

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void ShowSecondaryPrompt(FString _Text);

	UFUNCTION(BlueprintCallable, Category = "LD53")
	void HideSecondaryPrompt();
};
