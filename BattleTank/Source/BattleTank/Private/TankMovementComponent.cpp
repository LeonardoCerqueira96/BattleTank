// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("Moving towards tank %s, with velocity vector %s"),
		*(GetOwner()->GetName()), *MoveVelocity.ToString());
}

