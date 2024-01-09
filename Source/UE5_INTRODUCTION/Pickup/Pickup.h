// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"
UENUM()
enum class EPickupType : uint8
{
	Normal,
	DestroyAfterThrow,
	DestroyAfterPickup,
	Max UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FPickupStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPickupType PickupType = EPickupType::Normal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1.0", ClampMax = "10.0", EditCondition = "PickupType != EPickupType::Normal", EditConditionHides))
	float DestructionTimer = 5.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickupDestroyDelegate);

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UE5_INTRODUCTION_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();
protected:
	UPROPERTY(EditAnywhere, Category = "Pick Up")
	FPickupStruct PickupStruct;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Detonation
protected:
	FTimerHandle ProjectileDestructionTimerHandle;
public:
	void StartPickupDetonationTimer();
	void DestroyPickup();
	void ClearTimer();
	EPickupType GetPickupType() const { return PickupStruct.PickupType; }

	FOnPickupDestroyDelegate OnPickupDestroyDelegate;

};
