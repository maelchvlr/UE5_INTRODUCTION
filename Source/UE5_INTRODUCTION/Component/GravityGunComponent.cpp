// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/GravityGunComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Pickup/Pickup.h"
#include "Curves/CurveFloat.h"
#include "DataAsset/ThrowForceDataAsset.h"
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
	UpdatePickupLocation();
	updateTimeHold();
	// ...
}

void UGravityGunComponent::onTakeObjectInputPressed()
{

	//Check if hand are empty
	if (CurrentPickUp)
	{
		ReleasePickUp();
		return;
	}
		

	FVector RaycastStart = PlayerCameraManager->GetCameraLocation();
	FVector RaycastEnd = RaycastStart + PlayerCameraManager->GetActorForwardVector() * (RaycastSize + RaycastIncrease);

	//params
	FCollisionQueryParams params;
	params.AddIgnoredActor(MyCharacter);
	FHitResult hitResult;

#if !UE_BUILD_SHIPPING
	if (bDrawDebugRaycast)
		DrawDebugLine(GetWorld(), RaycastStart, RaycastEnd, FColor::Red, false, TimeDebugRaycast, 0.f, 5.f);

#endif

	bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, RaycastStart, RaycastEnd, GravityGunCollisionChannel, params);
	if (!bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit nothing"));
	}

	//Check type
	CurrentPickUp = Cast<APickup>(hitResult.GetActor());
	if (!CurrentPickUp)
		return;

	// Get cube mesh
	PickUpCube = CurrentPickUp->GetComponentByClass<UStaticMeshComponent>();
	if (!PickUpCube)
		return;

	// Disable physics
	PickUpCube->SetSimulatePhysics(false);

	//Update Collision Profile
	PreviousCollisionProfile = PickUpCube->GetCollisionProfileName();
	PickUpCube->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);


	if (CurrentPickUp->GetPickupType() != EPickupType::Normal)
	{
		CurrentPickUp->ClearTimer();
	}

	if(CurrentPickUp->GetPickupType() == EPickupType::DestroyAfterPickup)
	{
		CurrentPickUp->StartPickupDetonationTimer();

		CurrentPickUp->OnPickupDestroyDelegate.AddUniqueDynamic(this, &UGravityGunComponent::OnHoldPickupDestroyed);
	}

	UE_LOG(LogTemp, Log, TEXT("Hit %s"), *CurrentPickUp->GetName());
	OnPickupTake.Broadcast(CurrentPickUp->GetName());
}

void UGravityGunComponent::onThrowObjectInputPressed()
{
	
	if(!CurrentPickUp) return;
	startHolding = true;
	currentTimeHold = 0.f;
	throwStart = GetWorld()->GetTimeSeconds();

	
}

void UGravityGunComponent::onThrowObjectInputReleased()
{
	timeHeld = GetWorld()->GetTimeSeconds() - throwStart;
	if(timeHeld > MaxTimeHeld)
		timeHeld = MaxTimeHeld;
	if(timeHeld < MinTimeHeld)
		timeHeld = MinTimeHeld;
	
	if (!PickUpCube) return;
	ReleasePickUp(true);
	currentTimeHold = 0.f;
	startHolding = false;
}

void UGravityGunComponent::onDelete()
{
	if (CurrentPickUp)
	{
		CurrentPickUp->OnPickupDestroyDelegate.RemoveDynamic(this, &UGravityGunComponent::OnHoldPickupDestroyed);
		CurrentPickUp->DestroyPickup();

		CurrentPickUp = nullptr;
		PickUpCube = nullptr;
	}
}



void UGravityGunComponent::increaseRaycast()
{
	if (RaycastIncrease + RaycastSize + RaycastSizeIncrease < RaycastSizeMax)
	{
		RaycastIncrease += RaycastSizeIncrease;
		UE_LOG(LogTemp, Log, TEXT("increase : %f"), RaycastIncrease);
	}
}

void UGravityGunComponent::decreaseRaycast()
{
	if (RaycastIncrease >= RaycastSizeIncrease )
	{
		RaycastIncrease -= RaycastSizeIncrease;
		UE_LOG(LogTemp, Log, TEXT("decrease : %f"), RaycastIncrease);
	}
}

void UGravityGunComponent::setHand(APickup* pickup)
{
	CurrentPickUp = pickup;

	// Get cube mesh
	PickUpCube = CurrentPickUp->GetComponentByClass<UStaticMeshComponent>();
	if (!PickUpCube)
		return;

	// Disable physics
	PickUpCube->SetSimulatePhysics(false);

	//Update Collision Profile
	PreviousCollisionProfile = PickUpCube->GetCollisionProfileName();
	PickUpCube->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);


	if (CurrentPickUp->GetPickupType() != EPickupType::Normal)
	{
		CurrentPickUp->ClearTimer();
	}

	if (CurrentPickUp->GetPickupType() == EPickupType::DestroyAfterPickup)
	{
		CurrentPickUp->StartPickupDetonationTimer();

		CurrentPickUp->OnPickupDestroyDelegate.AddUniqueDynamic(this, &UGravityGunComponent::OnHoldPickupDestroyed);
	}

	UE_LOG(LogTemp, Log, TEXT("Hit %s"), *CurrentPickUp->GetName());
	OnPickupTake.Broadcast(CurrentPickUp->GetName());
}

void UGravityGunComponent::UpdatePickupLocation()
{
	if (!PickUpCube) return;

	FVector NewPickUplocation = PlayerCameraManager->GetCameraLocation() + PlayerCameraManager->GetActorForwardVector() * DistanceFromPlayer;
	CurrentPickUp->SetActorLocationAndRotation(NewPickUplocation, PlayerCameraManager->GetActorQuat());
}

void UGravityGunComponent::ReleasePickUp(bool bThrow)
{
	if(CurrentPickUp->GetPickupType() == EPickupType::DestroyAfterPickup)
	{
		CurrentPickUp->OnPickupDestroyDelegate.RemoveDynamic(this, &UGravityGunComponent::OnHoldPickupDestroyed);
	}

	// Set back physics
	PickUpCube->SetSimulatePhysics(true);

	// Set back collision profile
	PickUpCube->SetCollisionProfileName(PreviousCollisionProfile);


	// If throw pick up
	float Throwforce = 0.f;
	if (bThrow)
	{
		if (ThrowForceCurve)
		{
			Throwforce = ThrowForceCurve->GetFloatValue(timeHeld);
			UE_LOG(LogTemp, Log, TEXT("Throwforce : %f"), Throwforce);
		}
		else
		{
			if (ThrowForceDataAsset)
			{
				float ThrowForceAlpha = FMath::Clamp(timeHeld / ThrowForceDataAsset->TimeToReachMaxThrowForce, 0.f, 1.f);
				Throwforce = FMath::Lerp(ThrowForceDataAsset->MinThrowForce, ThrowForceDataAsset->MaxThrowForce, ThrowForceAlpha);
				UE_LOG(LogTemp, Log, TEXT("Throwforce : %f"), Throwforce);
			}
			else
			{
				float ThrowForceAlpha = FMath::Clamp(timeHeld / MaxTimeHeld, 0.f, 1.f);
				Throwforce = FMath::Lerp(timeHeld, MaxTimeHeld, ThrowForceAlpha);
				UE_LOG(LogTemp, Log, TEXT("Throwforce : %f"), Throwforce);
			}
		}
		FVector Impulse = PlayerCameraManager->GetActorForwardVector() * (PickUpThrowForce * timeHeld);
		PickUpCube->AddImpulse(Impulse, NAME_None, true);
		FVector AngularImpulse = FVector(FMath::RandRange(.0, PickUpAngularForce.X), FMath::RandRange(.0, PickUpAngularForce.Y), FMath::RandRange(.0, PickUpAngularForce.Z));
		PickUpCube->AddAngularImpulseInDegrees(AngularImpulse, NAME_None, true);
	}

	//Check if destruction timer required
	if(CurrentPickUp->GetPickupType() == EPickupType::DestroyAfterThrow)
	{
		CurrentPickUp->StartPickupDetonationTimer();
	}


	// clean refs
	CurrentPickUp = nullptr;
	PickUpCube = nullptr;
}

void UGravityGunComponent::OnHoldPickupDestroyed(APickup* pickup)
{
	CurrentPickUp->OnPickupDestroyDelegate.RemoveDynamic(this, &UGravityGunComponent::OnHoldPickupDestroyed);

	ReleasePickUp();
}

float UGravityGunComponent::GetTimeToReachMaxThrowForce()
{
	return MaxTimeHeld;
}

float UGravityGunComponent::GetTimeHeld()
{
	return timeHeld;
}

void UGravityGunComponent::updateTimeHold()
{
	if(!startHolding) return;
	currentTimeHold = GetWorld()->GetTimeSeconds() - throwStart;
}

