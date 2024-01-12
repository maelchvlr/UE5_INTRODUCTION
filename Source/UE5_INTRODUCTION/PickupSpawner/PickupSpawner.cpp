// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSpawner/PickupSpawner.h"
#include "Component/GravityGunComponent.h"
#include "Pickup/Pickup.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UPickupSpawner::UPickupSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPickupSpawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APickup::StaticClass(), PickupArray);
	for (auto pickup : PickupArray)
	{
		CurrentPickupAmount++;
		auto CastedPickup = Cast<APickup>(pickup);
		CastedPickup->OnPickupDestroyDelegate.AddDynamic(this, &UPickupSpawner::OnPickupDestroy);
		for (auto& amount : PickupAmounts)
		{
			if (amount.GetPickupType() == CastedPickup->GetPickupType())
			{
				amount.addCurrentAmount();
			}
		}
	}
	
}


// Called every frame
void UPickupSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (SpawnDelayTimer > 0.0f)
	{
		SpawnDelayTimer -= DeltaTime;
	}

	// ...
}

bool UPickupSpawner::SpawnPickup(TSubclassOf<APickup> pickupType)
{
	if (SpawnDelayTimer > 0.0f)
	{
		return false;
	}
	UWorld* World = GetWorld(); 
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		FRotator Rotation = FRotator::ZeroRotator;
		FVector PlayerLocation = GetOwner()->GetActorLocation();
		FVector PlayerForwardVector = GetOwner()->GetActorForwardVector();


		FVector Location = PlayerLocation + PlayerForwardVector * 100.0f;
		APickup* PickupSpawned = World->SpawnActor<APickup>(pickupType, Location, Rotation, SpawnParams);
		PickupSpawned->OnPickupDestroyDelegate.AddDynamic(this, &UPickupSpawner::OnPickupDestroy);
		PickupArray.Add(PickupSpawned);
		CurrentPickupAmount++;
		SpawnDelayTimer = SpawnDelay;
		OnPickupSpawn.Broadcast(PickupSpawned);
		return true;
	}
	else
		return false;

	
}

void UPickupSpawner::ShowTotalPickupAmount()
{
	UE_LOG(LogTemp, Warning, TEXT("Total Pickup Amount: %i"), CurrentPickupAmount);
}

void UPickupSpawner::SpawnPickupIfPossible(TSubclassOf<APickup> PickupType)
{
	UE_LOG(LogTemp, Warning, TEXT("SpawnPickupIfPossible"));
	for (auto& amount : PickupAmounts)
	{
		if (amount.GetPickup() == PickupType && amount.GetCurrentAmount() < amount.GetMaxAmount() && CurrentPickupAmount < MaxPickupAmount)
		{
			UE_LOG(LogTemp, Warning, TEXT("current amount %i"), amount.GetCurrentAmount());
			if(SpawnPickup(PickupType))
				amount.addCurrentAmount();
			return;
		}
	}
}

void UPickupSpawner::OnPickupDestroy(APickup* Pickup)
{
	UE_LOG(LogTemp, Warning, TEXT("OnPickupDestroy called"));
	for (auto &amount : PickupAmounts)
	{
		if (amount.GetPickupType() == Pickup->GetPickupType())
		{
			amount.removeCurrentAmount();
		}
	}
	PickupArray.Remove(Pickup);
	CurrentPickupAmount--;
}




