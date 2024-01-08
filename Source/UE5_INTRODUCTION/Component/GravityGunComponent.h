// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityGunComponent.generated.h"


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
	void SetCharacter(class AMyCharacter* InCharacter) { MyCharacter = InCharacter; }

// Collision
	UPROPERTY(EditAnywhere, Category = "GravityGun | Collision")
	TEnumAsByte<ETraceTypeQuery> simpleCollisionTraceChannel;

    UPROPERTY(EditAnywhere, Category = "GravityGun | Collision", meta = (ClampMin = "0.0", ClampMax="3000.0"))
	float RaycastSize = 500.0f;

	class AMyCharacter* MyCharacter = nullptr;

	TWeakObjectPtr<class APlayerCameraManager> PlayerCameraManager = nullptr;

	ECollisionChannel GravityGunCollisionChannel;
		
};
