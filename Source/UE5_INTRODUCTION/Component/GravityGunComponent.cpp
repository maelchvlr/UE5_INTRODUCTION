// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/GravityGunComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MyCharacter.h"

// Sets default values for this component's properties
UGravityGunComponent::UGravityGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGravityGunComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	GravityGunCollisionChannel = UEngineTypes::ConvertToCollisionChannel(simpleCollisionTraceChannel);
	
}


// Called every frame
void UGravityGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGravityGunComponent::onTakeObjectInputPressed()
{
	FVector RaycastStart = PlayerCameraManager->GetCameraLocation();
	FVector RaycastEnd = RaycastStart + PlayerCameraManager->GetActorForwardVector() * RaycastSize;

	//params
	FCollisionQueryParams params;
	params.AddIgnoredActor(MyCharacter);
	FHitResult hitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, RaycastStart, RaycastEnd, GravityGunCollisionChannel, params);
	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit"));
	}
}

void UGravityGunComponent::onThrowObjectInputPressed()
{
}

