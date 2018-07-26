// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %.4f"), *GetName(), Throttle);
}


