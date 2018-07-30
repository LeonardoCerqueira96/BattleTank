// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


// Enum for firing state
UENUM()
enum class EFiringState : uint8 
{ 
	Reloading, 
	Aiming, 
	Locked 
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	
	void AimAt(FVector AimLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void FireProjectile();

	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading;

private:
	// The initial projectile launch speed
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 5000.f;
	
	// A reference to the tank barrel
	UTankBarrel* Barrel = nullptr;

	// A reference to the tank turret
	UTankTurret* Turret = nullptr;

	// Reference to the projectile blueprint to be spawned on the Fire method
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Time when the tank last fired
	double LastFireTime = 0;

	// The time it takes to reload the gun
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.f;

	// Variable with the target direction the barrel is moving towards
	FVector CurrentTargetDirection;

	// Method to move the barrel towards a target direction
	void MoveBarrelTowardsDirection();

	// Tell if the barrel is currently moving
	bool IsBarrelMoving() const;
};
