// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MyPlayerController.h"
#include "Character/MyCharacter.h"
#include "Component/GravityGunController.h"
#include "Kismet/GameplayStatics.h"
#include "Goal/Goal.h"

void AMyPlayerController::MoveForward(float Value)
{
	if(!IsValid(MyCharacter))
	{
		return;
	}

	if(Value == 0.0f)
	{
		return;
	}

	MyCharacter->AddMovementInput(MyCharacter->GetActorForwardVector(), Value);
	
}

void AMyPlayerController::MoveRight(float Value)
{
	if (!IsValid(MyCharacter))
	{
		return;
	}

	if (Value == 0.0f)
	{
		return;
	}

	MyCharacter->AddMovementInput(MyCharacter->GetActorRightVector(), Value);
}

void AMyPlayerController::Jump()
{
	if (!IsValid(MyCharacter))
	{
		return;
	}

	MyCharacter->Jump();
}

void AMyPlayerController::CountScore()
{
	if (Goals.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Goals Found"));
	}

	for (AActor* Goal : Goals)
	{
		AGoal* CastedGoal = Cast<AGoal>(Goal);
		if (CastedGoal)
		{
			int PickupInGoal = CastedGoal->CountPickupInGoal();
			UE_LOG(LogTemp, Log, TEXT("Pickup in %s: %d"), *Goal->GetName(), PickupInGoal);
			
		}
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Bind Movement
	InputComponent->BindAxis(MoveForwardInput, this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis(MoveRightInput, this, &AMyPlayerController::MoveRight);

	InputComponent->BindAction(JumpInput, IE_Pressed, this, &AMyPlayerController::Jump);

	// Bind Score
	FInputActionBinding ScoreInputActionBinding = InputComponent->BindAction(CountScoreInput, IE_Pressed, this, &AMyPlayerController::CountScore);
	ScoreInputActionBinding.bConsumeInput = false;
}

void AMyPlayerController::SetupCameraComponent()
{
	InputComponent->BindAxis(LookUpInput, MyCharacter, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis(LookRightInput, MyCharacter, &APawn::AddControllerYawInput);
}

void AMyPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	MyCharacter = Cast<AMyCharacter>(InPawn);

	SetupCameraComponent();
}

void AMyPlayerController::AddPitchInput(float Value)
{
	float Multiplier = Value * MouseSensitivityX;
	Super::AddPitchInput(Multiplier);

}

void AMyPlayerController::AddYawInput(float Value)
{
	float Multiplier = Value * MouseSensitivityY;
	Super::AddYawInput(Multiplier);
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->OnWorldBeginPlay.AddUObject(this, &AMyPlayerController::LateBeginPlay);

	// Get All Goals
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGoal::StaticClass(), Goals);
	if (Goals.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Goals Found"));
	}	

}

void AMyPlayerController::LateBeginPlay()
{
	GravityGunController = GetComponentByClass<UGravityGunController>();
	if (IsValid(GravityGunController))
	{
		GravityGunController->setupInputComponentGravityGun(MyCharacter, InputComponent);
	}
}
