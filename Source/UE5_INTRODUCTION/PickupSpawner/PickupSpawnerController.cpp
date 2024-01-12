// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSpawner/PickupSpawnerController.h"
#include "PickupSpawner/PickupSpawner.h"
#include "Pickup/Pickup.h"
#include "Character/MyCharacter.h"
#include <Kismet/GameplayStatics.h>


// Sets default values for this component's properties
UPickupSpawnerController::UPickupSpawnerController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPickupSpawnerController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPickupSpawnerController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPickupSpawnerController::setupInputComponentPickupSpawner(AMyCharacter* InCharacter, TObjectPtr<class UInputComponent> InputComponent)
{
	MyCharacter = InCharacter;
	PickupSpawner = MyCharacter->GetComponentByClass<UPickupSpawner>();

	//bind action
	InputComponent->BindAction(SpawnNormalInput, IE_Pressed, this, &UPickupSpawnerController::OnSpawnNormalInputPressed);
	InputComponent->BindAction(SpawnDestroyThrowInput, IE_Pressed, this, &UPickupSpawnerController::OnSpawnDestroyThrowInputPressed);
	InputComponent->BindAction(SpawnDestroyPickupInput, IE_Pressed, this, &UPickupSpawnerController::OnSpawnDestroyPickupInputPressed);
	InputComponent->BindAction(ShowTotalPickupAmountInput, IE_Pressed, this, &UPickupSpawnerController::ShowTotalPickupAmount);
}


void UPickupSpawnerController::OnSpawnNormalInputPressed()
{
	if(PickupSpawner)
			PickupSpawner->SpawnPickupIfPossible(PickupNormal);
}

void UPickupSpawnerController::OnSpawnDestroyThrowInputPressed()
{
	if(PickupSpawner)
			PickupSpawner->SpawnPickupIfPossible(PickupDestroyThrow);
}

void UPickupSpawnerController::OnSpawnDestroyPickupInputPressed()
{
	if(PickupSpawner)
			PickupSpawner->SpawnPickupIfPossible(PickupDestroyPickup);
}

void UPickupSpawnerController::ShowTotalPickupAmount()
{
	if(PickupSpawner)
			PickupSpawner->ShowTotalPickupAmount();
}


