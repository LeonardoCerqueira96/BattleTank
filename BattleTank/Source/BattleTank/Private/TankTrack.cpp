// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceApplied = GetForwardVector() * TrackMaxDrivingForce * Throttle;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


