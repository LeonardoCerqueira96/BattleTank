// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetPawn()->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation_OUT) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(CrosshairXLocation * ViewportSizeX, CrosshairYLocation * ViewportSizeY);
	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, HitLocation_OUT);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection_OUT) const
{
	FVector WorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X, 
		ScreenLocation.Y,
		WorldLocation, 
		LookDirection_OUT
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& WorldHitLocation) const
{
	FHitResult HitResult;
	FVector LineTraceStart = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = LineTraceStart + LookDirection * LineTraceRange;
	FCollisionQueryParams QueryParams = FCollisionQueryParams(NAME_None, false, GetPawn());

	bool bTraceHitSomething = GetWorld()->LineTraceSingleByChannel
	(
		HitResult,
		LineTraceStart,
		LineTraceEnd,
		ECollisionChannel::ECC_Visibility,
		QueryParams,
		FCollisionResponseParams::DefaultResponseParam
	);

	WorldHitLocation = bTraceHitSomething ? HitResult.Location : FVector(0.f);
	return bTraceHitSomething;
}

