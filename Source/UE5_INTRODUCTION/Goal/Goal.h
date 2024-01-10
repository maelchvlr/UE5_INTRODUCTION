// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

UENUM()
enum class ETeam : uint8
{
	Blue,
	Red
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTeamScored, ETeam, Team);

UCLASS()
class UE5_INTRODUCTION_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoal(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Collision Box
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBoxComponent* CollisionBox = nullptr;
	unsigned int score = 0;

	UPROPERTY(EditAnywhere, Category = "Goal | Collision")
	TEnumAsByte<ETraceTypeQuery> GoalCollisionTraceChannel;

public:
	UFUNCTION()
	void OnReceivingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	int CountPickupInGoal();

	FTeamScored TeamScored;

	//Team
protected:
	UPROPERTY(EditAnywhere, Category = "Goal | Team")
	ETeam Team = ETeam::Blue;
};
