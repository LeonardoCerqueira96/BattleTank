// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"

UTankAimingComponent::UTankAimingComponent()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	if (!ensure(Barrel && Turret)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		AimLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHasAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		CurrentTargetDirection = AimDirection;
		MoveBarrelTowardsDirection();
	}
}

void UTankAimingComponent::MoveBarrelTowardsDirection()
{
	if (!ensure(Barrel && Turret)) { return; }
	
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator DeltaRotator = CurrentTargetDirection.Rotation() - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Turn(DeltaRotator.Yaw);
}

void UTankAimingComponent::FireProjectile()
{
	if (ensure(Barrel) && FiringState != EFiringState::Reloading)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>
		(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) { return false; }
	
	return !CurrentTargetDirection.Equals(Barrel->GetForwardVector(), 0.01f);
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

