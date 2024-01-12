// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/Pickup.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::StartPickupDetonationTimer()
{
	float DestructionTime = PickupStruct.DestructionTimer;

	//Prepare Timer
	FTimerManager& TimerManager = this->GetWorldTimerManager();
	TimerManager.ClearTimer(ProjectileDestructionTimerHandle);
	TimerManager.SetTimer(ProjectileDestructionTimerHandle, this, &APickup::DestroyPickup, DestructionTime, false);
}

void APickup::DestroyPickup()
{
	//Clear timer
	ClearTimer();
	OnPickupDestroyDelegate.Broadcast(this);
	Destroy();
}

void APickup::ClearTimer()
{
	FTimerManager& TimerManager = this->GetWorldTimerManager();
	TimerManager.ClearTimer(ProjectileDestructionTimerHandle);
}

