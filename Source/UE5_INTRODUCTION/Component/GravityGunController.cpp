// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/GravityGunController.h"
#include "Component/GravityGunComponent.h"
#include "Character/MyCharacter.h"

// Sets default values for this component's properties
UGravityGunController::UGravityGunController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
}


// Called when the game starts
void UGravityGunController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UGravityGunController::setupInputComponentGravityGun(AMyCharacter* InCharacter, TObjectPtr<class UInputComponent> InputComponent)
{
	MyCharacter = InCharacter;
	GravityGunComponent = MyCharacter->GetComponentByClass<UGravityGunComponent>();
	GravityGunComponent->SetCharacter(MyCharacter);

	//bind action
	InputComponent->BindAction(TakeObjectInput, IE_Pressed, this, &UGravityGunController::OnTakeObjectInputPressed);
	InputComponent->BindAction(ThrowObjectInput, IE_Pressed, this, &UGravityGunController::OnThrowObjectInputPressed);
}

void UGravityGunController::OnTakeObjectInputPressed()
{
	if (GravityGunComponent)
	{
		GravityGunComponent->onTakeObjectInputPressed();
	}
}

void UGravityGunController::OnThrowObjectInputPressed()
{
	if (GravityGunComponent)
	{
		GravityGunComponent->onThrowObjectInputPressed();
	}
}

