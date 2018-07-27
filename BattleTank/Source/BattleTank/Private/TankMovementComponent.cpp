// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"

UTankMovementComponent::UTankMovementComponent()
{

}

float UTankMovementComponent::IntendMoveForward(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward: %.4f"), Throw);
	return 0.f;
}


