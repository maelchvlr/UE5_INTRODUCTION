// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal/Goal.h"
#include "Components/BoxComponent.h"
#include "Pickup/Pickup.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AGoal::AGoal(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Collision Box
	CollisionBox = ObjectInitializer.CreateOptionalDefaultSubobject<UBoxComponent>(this, TEXT("CollisionBox"));
	if (CollisionBox)
	{
		SetRootComponent(CollisionBox);
	}
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGoal::OnReceivingOverlap);
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoal::OnReceivingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APickup* EnteringPickup = Cast<APickup>(OtherActor);
	if (EnteringPickup)
	{
		score++;
	}
	UE_LOG(LogTemp, Log, TEXT("Score: %d"), score);
	TeamScored.Broadcast(Team);
}

int AGoal::CountPickupInGoal()
{
	//Prepare raycast location
	FVector GoalLocation = GetActorLocation();
	FVector ScaledBoxExtent = CollisionBox->GetScaledBoxExtent();

	// Launch raycast
	const TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> OutHits;
	UKismetSystemLibrary::BoxTraceMulti(GetWorld(), GoalLocation, GoalLocation, ScaledBoxExtent,
		GetActorRotation(), GoalCollisionTraceChannel, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true);

	int NumberOfPickupInGoal = OutHits.Num();
	return NumberOfPickupInGoal;
}

