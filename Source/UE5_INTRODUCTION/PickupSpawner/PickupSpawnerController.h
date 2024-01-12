// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Pickup/Pickup.h"
#include "PickupSpawnerController.generated.h"



UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_INTRODUCTION_API UPickupSpawnerController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupSpawnerController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Input
protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	FName SpawnNormalInput;

	UPROPERTY(EditAnywhere, Category = "Input")
	FName SpawnDestroyThrowInput;

	UPROPERTY(EditAnywhere, Category = "Input")
	FName SpawnDestroyPickupInput;

	UPROPERTY(EditAnywhere, Category = "Input")
	FName ShowTotalPickupAmountInput;

	//Pickups
protected:
	UPROPERTY(EditAnywhere, Category = "Pickups")
	TSubclassOf<APickup> PickupNormal;

	UPROPERTY(EditAnywhere, Category = "Pickups")
	TSubclassOf<APickup> PickupDestroyThrow;

	UPROPERTY(EditAnywhere, Category = "Pickups")
	TSubclassOf<APickup> PickupDestroyPickup;

	//Character
protected:
	class AMyCharacter* MyCharacter = nullptr;

	//PickupSpawner
protected:
	class UPickupSpawner* PickupSpawner = nullptr;

	//Setup Input
public:
	void setupInputComponentPickupSpawner(class AMyCharacter* InCharacter, TObjectPtr<class UInputComponent> InputComponent);
	class UPickupSpawner* GetPickupSpawner() { return PickupSpawner; }

	//Input functions
protected:
	void OnSpawnNormalInputPressed();
	void OnSpawnDestroyThrowInputPressed();
	void OnSpawnDestroyPickupInputPressed();
	void ShowTotalPickupAmount();

	//Pickup Amount
protected:
	TArray<class AActor*> PickupArray;

		
};
