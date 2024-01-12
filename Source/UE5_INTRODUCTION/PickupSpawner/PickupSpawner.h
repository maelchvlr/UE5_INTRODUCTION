// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup/Pickup.h"
#include "Components/ActorComponent.h"
#include "PickupSpawner.generated.h"

USTRUCT(BlueprintType)
struct FPickupAmount
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APickup> pickup;

	UPROPERTY(EditAnywhere)
	EPickupType pickupType = EPickupType::Normal;

	UPROPERTY(EditAnywhere)
	int maxAmount = 0;

	int currentAmount = 0;

public:
	TSubclassOf<APickup> GetPickup() { return pickup; }
	EPickupType GetPickupType() { return pickupType; }
	int GetMaxAmount() { return maxAmount; }
	int GetCurrentAmount() { return currentAmount; }
	void addCurrentAmount() { currentAmount += 1; }
	void removeCurrentAmount() { currentAmount -= 1; }

};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickupSpawnedDelegate, class APickup*, Pickup);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_INTRODUCTION_API UPickupSpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupSpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

	//Spawn Pickups
public:
	UFUNCTION(BlueprintCallable)
	bool SpawnPickup(TSubclassOf<class APickup> pickupType);

	UFUNCTION(BlueprintCallable)
	void ShowTotalPickupAmount();

	//Spawn parameters
protected:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float SpawnDelay = 1.0f;

	float SpawnDelayTimer = SpawnDelay;

	//Pickup handling
protected:
	class UGravityGunComponent* GravityGunComponent = nullptr;

	//Delegates
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPickupSpawnedDelegate OnPickupSpawn;

	//Pickup Amount

public:
	void SpawnPickupIfPossible(TSubclassOf<APickup> PickupType);

	UFUNCTION()
	void OnPickupDestroy(APickup* Pickup);

protected:
	UPROPERTY(EditAnywhere, Category = "Pickup Amount")
	TArray<FPickupAmount> PickupAmounts;

	UPROPERTY(EditAnywhere, Category = "Pickup Amount")
	int MaxPickupAmount = 7;

	int CurrentPickupAmount = 0;

	TArray<class AActor*> PickupArray;




		
};
