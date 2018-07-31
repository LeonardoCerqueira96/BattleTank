// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* ControlledPawn = GetPawn();
	UTankAimingComponent* AimingComponent = ControlledPawn->FindComponentByClass<UTankAimingComponent>();

	if (ensure(PlayerPawn))
	{
		AimingComponent->AimAt(PlayerPawn->GetActorLocation());
		
		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->FireProjectile();
		}

		MoveToActor(PlayerPawn, AcceptanceRadius);
	}
}




