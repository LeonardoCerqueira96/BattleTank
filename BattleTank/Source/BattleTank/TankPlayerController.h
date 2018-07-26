// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.f;
	
	ATank* GetControlledTank() const;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation_OUT) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection_OUT) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& WorldHitLocation) const;
};
