// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Goal/Goal.h"
#include "Components/ActorComponent.h"
#include "ScoreComponent.generated.h"

USTRUCT()
struct FTeamStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	ETeam team = ETeam::Blue;

protected:
	UPROPERTY(VisibleAnywhere)
	int score = 0;

public:
	void updateScore(int value)
	{
		score += value;
	}

	void DisplayScore()
	{
		UE_LOG(LogTemp, Log, TEXT("Team %d has %d points"), team, score);
	}

};

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_INTRODUCTION_API UScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScoreComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Score")
	TArray<FTeamStruct> teams;

	TArray<AActor*> goals;

public:
	UFUNCTION()
	void OnTeamScored(ETeam team);

		
};
