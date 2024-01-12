// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UE5_INTRODUCTION_API UPauseMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OpenMenu();

	UFUNCTION(BlueprintCallable)
	void ResumeGame();

	UFUNCTION(BlueprintCallable)
	void RestartGame();

	UFUNCTION(BlueprintCallable)
	void QuitGame();

	UFUNCTION(BlueprintCallable)
	void ReturnToMainMenu();

	UFUNCTION(BlueprintCallable)
	void OpenOptionMenu();

	UFUNCTION(BlueprintCallable)
	void ReceiveXSliderValue(float Value);

	UFUNCTION(BlueprintCallable)
	void ReceiveYSliderValue(float Value);



protected:
	class AMyPlayerController* PlayerController = nullptr;

protected:
	virtual void NativeConstruct() override;

	//Button
	UPROPERTY(meta = (BindWidgetOptional))
	class UButton* RESUME_Button;
	UPROPERTY(meta = (BindWidgetOptional))
	class UButton* RESTART_Button;
	UPROPERTY(meta = (BindWidgetOptional))
	class UButton* QUIT_Button;
	UPROPERTY(meta = (BindWidgetOptional))
	class UButton* RETURNMAINMENU_Button;
	UPROPERTY(meta = (BindWidgetOptional))
	class UButton* OPTION_Button;

	UPROPERTY(meta = (BindWidgetOptional))
	class UVerticalBox* MAIN_VerticalBox;
	UPROPERTY(meta = (BindWidgetOptional))
	class UVerticalBox* OPTION_VerticalBox;

	UPROPERTY(meta = (BindWidgetOptional))
	class USlider* XSlider;
	UPROPERTY(meta = (BindWidgetOptional))
	class USlider* YSlider;

	UPROPERTY(meta = (BindWidgetOptional))
	class UTextBlock* XSliderValue;
	UPROPERTY(meta = (BindWidgetOptional))
	class UTextBlock* YSliderValue;

};
