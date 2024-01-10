// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityGunComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickupTakenDelegate, FString, PickupName);

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_INTRODUCTION_API UGravityGunComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGravityGunComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void onTakeObjectInputPressed();
	void onThrowObjectInputPressed();
	void onThrowObjectInputReleased();
	void increaseRaycast();
	void decreaseRaycast();
	void SetCharacter(class AMyCharacter* InCharacter) { MyCharacter = InCharacter; }

// Collision
	UPROPERTY(EditAnywhere, Category = "GravityGun | Collision")
	TEnumAsByte<ETraceTypeQuery> simpleCollisionTraceChannel;

    UPROPERTY(EditAnywhere, Category = "GravityGun | Collision", meta = (ClampMin = "0.0", ClampMax="3000.0"))
	float RaycastSize = 500.0f;

	UPROPERTY(EditAnywhere, Category = "GravityGun | Collision")
	float RaycastSizeMax = 3000.0f;

	UPROPERTY(EditAnywhere, Category = "GravityGun | Collision")
	float RaycastSizeIncrease = 200.f;

	class AMyCharacter* MyCharacter = nullptr;

	TWeakObjectPtr<class APlayerCameraManager> PlayerCameraManager = nullptr;

	ECollisionChannel GravityGunCollisionChannel;

	//Pick up
protected:
	float RaycastIncrease;
	float throwStart;
	float timeHeld;
	class APickup* CurrentPickUp = nullptr;
	UStaticMeshComponent* PickUpCube = nullptr;
	FName PreviousCollisionProfile = NAME_None;

	UPROPERTY(EditAnywhere, Category = "GravityGun | Pickup")
	float DistanceFromPlayer = 300.0f;

	UPROPERTY(EditAnywhere, Category = "GravityGun | Pickup")
	float PickUpThrowForce = 2000.0f;

	UPROPERTY(EditAnywhere, Category = "GravityGun | Pickup")
	FVector PickUpAngularForce = FVector(2000.0f);

	UPROPERTY(EditAnywhere, Category = "GravityGun | Pickup")
	float MaxTimeHeld = 2.0;

	UPROPERTY(EditAnywhere, Category = "GravityGun | Pickup")
	float MinTimeHeld = 1.0;

	//Debug
protected:
	UPROPERTY(EditAnywhere, Category = "GravityGun | Debug")
	bool bDrawDebugRaycast = false;
	UPROPERTY(EditAnywhere, Category = "GravityGun | Debug", meta = (ClampMin = "0.1", ClampMax = "30.0"))
	float TimeDebugRaycast = 5.f;

protected:
	void UpdatePickupLocation();
	void ReleasePickUp(bool bThrow = false);

	// Event on pickup destroy
protected:
	UFUNCTION()
	void OnHoldPickupDestroyed();

	//Exemple of delegate
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPickupTakenDelegate OnPickupTake;
		
};
