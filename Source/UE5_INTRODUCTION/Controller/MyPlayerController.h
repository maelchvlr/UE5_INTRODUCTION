// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE5_INTRODUCTION_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	//Movement
	UPROPERTY(EditAnywhere, Category = "Inputs | Movements")
	FName MoveForwardInput;

	UPROPERTY(EditAnywhere, Category = "Inputs | Movements")
	FName MoveRightInput;

	//Jump
	UPROPERTY(EditAnywhere, Category = "Inputs | Jump")
	FName JumpInput;

	//Camera
	UPROPERTY(EditAnywhere, Category = "Inputs | Mouse")
	FName LookUpInput;

	UPROPERTY(EditAnywhere, Category = "Inputs | Mouse")
	FName LookRightInput;

	UPROPERTY(EditAnywhere, Category = "Inputs | Score")
	FName CountScoreInput;

	//Pause
	UPROPERTY(EditAnywhere, Category = "Inputs | Pause")
	FName PauseInputName = FName();

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void SetupCameraComponent();
	void Jump();

	//Score
protected:
	void CountScore();

protected:
	TArray<AActor*> Goals;


public:
	virtual void SetupInputComponent() override;
	virtual void SetPawn(APawn* InPawn) override;

//Camera Sensitivity
protected:
	UPROPERTY(EditAnywhere, Category = "Inputs | Mouse")
	float MouseSensitivityX = 1.0f;
	
	UPROPERTY(EditAnywhere, Category = "Inputs | Mouse")
	float MouseSensitivityY = 1.0f;

public:
	void AddPitchInput(float Value) override;
	void AddYawInput(float Value) override;

//Character
protected:
	class AMyCharacter* MyCharacter = nullptr;

//Gravity Gun
protected:
	class UGravityGunController* GravityGunController = nullptr;

//Pickup Spawner
protected:
	class UPickupSpawnerController* PickupSpawnerController = nullptr;

public:
	UFUNCTION()
	void OnPickupSpawn(class APickup* pickup);

public:
	virtual void BeginPlay() override;
	void LateBeginPlay();


	//Pause
protected:
	UPROPERTY(EditAnywhere, Category = "Pause")
	TSubclassOf<class UPauseMenuUserWidget> PauseMenuWidget = nullptr;


protected:
	void OnPauseInputPressed();

	//Sensitivity update from menu
public:
	float GetXSensitivity();
	float GetYSensitivity();

	void SetXSensitivity(float Value);
	void SetYSensitivity(float Value);
};
