// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ScoreComponent.h"
#include "Goal/Goal.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UScoreComponent::UScoreComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UScoreComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// Get All Goals
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGoal::StaticClass(), goals);
	for (auto goal : goals)
	{
		AGoal* CastedGoal = Cast<AGoal>(goal);
		CastedGoal->TeamScored.AddUniqueDynamic(this, &UScoreComponent::OnTeamScored);
	}
	
}


// Called every frame
void UScoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UScoreComponent::OnTeamScored(ETeam teamIn)
{
	for (auto &team : teams)
	{
		if (team.team == teamIn)
		{
			team.updateScore(1);
			
		}
		team.DisplayScore();
	}
}


