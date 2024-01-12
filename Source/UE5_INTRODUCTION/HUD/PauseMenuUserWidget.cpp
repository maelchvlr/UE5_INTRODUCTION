// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PauseMenuUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Controller/MyPlayerController.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

void UPauseMenuUserWidget::OpenMenu()
{
	SetVisibility(ESlateVisibility::Visible);
	
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(FInputModeUIOnly());
	}

	UGameplayStatics::SetGamePaused(this, true);
}

void UPauseMenuUserWidget::ResumeGame()
{
	SetVisibility(ESlateVisibility::Collapsed);
	RemoveFromParent();
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(FInputModeGameOnly());
	}

	UGameplayStatics::SetGamePaused(this, false);
}

void UPauseMenuUserWidget::RestartGame()
{
	FName LevelName = FName(*UGameplayStatics::GetCurrentLevelName(this));
	UGameplayStatics::OpenLevel(this, LevelName);
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
}

void UPauseMenuUserWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true);
}

void UPauseMenuUserWidget::ReturnToMainMenu()
{
	MAIN_VerticalBox->SetVisibility(ESlateVisibility::Visible);
	OPTION_VerticalBox->SetVisibility(ESlateVisibility::Collapsed);

}

void UPauseMenuUserWidget::OpenOptionMenu()
{
	MAIN_VerticalBox->SetVisibility(ESlateVisibility::Collapsed);
	OPTION_VerticalBox->SetVisibility(ESlateVisibility::Visible);
}

void UPauseMenuUserWidget::ReceiveXSliderValue(float Value)
{
	if (PlayerController)
	{
		PlayerController->SetXSensitivity(Value);
		XSliderValue->SetText(FText::FromString(FString::SanitizeFloat(PlayerController->GetXSensitivity())));
	}
}

void UPauseMenuUserWidget::ReceiveYSliderValue(float Value)
{
	if (PlayerController)
	{
		PlayerController->SetYSensitivity(Value);
		YSliderValue->SetText(FText::FromString(FString::SanitizeFloat(PlayerController->GetYSensitivity())));
	}
}

void UPauseMenuUserWidget::NativeConstruct()
{	
	Super::NativeConstruct();
	PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	OpenMenu();

	if (RESUME_Button)
	{
		UE_LOG(LogTemp, Warning, TEXT("RESUME_Button"));
		RESUME_Button->OnClicked.AddUniqueDynamic(this, &UPauseMenuUserWidget::ResumeGame);
	}

	if (RESTART_Button)
	{
		UE_LOG(LogTemp, Warning, TEXT("RESTART_Button"));
		RESTART_Button->OnClicked.AddUniqueDynamic(this, &UPauseMenuUserWidget::RestartGame);
	}

	if (QUIT_Button)
	{
		UE_LOG(LogTemp, Warning, TEXT("QUIT_Button"));
		QUIT_Button->OnClicked.AddUniqueDynamic(this, &UPauseMenuUserWidget::QuitGame);
	}

	if (RETURNMAINMENU_Button)
	{
		UE_LOG(LogTemp, Warning, TEXT("RETURNTOMAINMENU_Button"));
		RETURNMAINMENU_Button->OnClicked.AddUniqueDynamic(this, &UPauseMenuUserWidget::ReturnToMainMenu);
	}

	if (OPTION_Button)
	{
		UE_LOG(LogTemp, Warning, TEXT("OPTION_Button"));
		OPTION_Button->OnClicked.AddUniqueDynamic(this, &UPauseMenuUserWidget::OpenOptionMenu);
	}

	ReturnToMainMenu();

	if (XSlider)
	{
		XSlider->OnValueChanged.AddUniqueDynamic(this, &UPauseMenuUserWidget::ReceiveXSliderValue);
		XSlider->SetValue(PlayerController->GetXSensitivity());
	}

	if (YSlider)
	{
		YSlider->OnValueChanged.AddUniqueDynamic(this, &UPauseMenuUserWidget::ReceiveYSliderValue);
		YSlider->SetValue(PlayerController->GetYSensitivity());
	}

	if (XSliderValue)
	{
		XSliderValue->SetText(FText::FromString(FString::SanitizeFloat(PlayerController->GetXSensitivity())));
	}

	if (YSliderValue)
	{
		YSliderValue->SetText(FText::FromString(FString::SanitizeFloat(PlayerController->GetYSensitivity())));
	}

}
