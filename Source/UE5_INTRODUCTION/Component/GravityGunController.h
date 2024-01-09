// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityGunController.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_INTRODUCTION_API UGravityGunController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGravityGunController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	FName TakeObjectInput;

	UPROPERTY(EditAnywhere, Category = "Input")
	FName ThrowObjectInput;

	UPROPERTY(EditAnywhere, Category = "Input")
	FName IncreaseRaycast;

	UPROPERTY(EditAnywhere, Category = "Input")
	FName DecreaseRaycast;

protected:
	class AMyCharacter* MyCharacter = nullptr;
	class UGravityGunComponent* GravityGunComponent = nullptr;

public:
	void setupInputComponentGravityGun(class AMyCharacter* InCharacter, TObjectPtr<class UInputComponent> InputComponent);

protected:
	void OnTakeObjectInputPressed();
	void OnThrowObjectInputPressed();
	void OnThrowObjectInputReleased();
	void increaseRaycast();
	void decreaseRaycast();

		
};
