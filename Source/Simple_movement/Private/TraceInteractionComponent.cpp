// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework


#include "TraceInteractionComponent.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "InteractiveObject.h"

UTraceInteractionComponent::UTraceInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bUsingLineTrace = true;
}


// Called when the game starts
void UTraceInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTraceInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FHitResult hit;
	bool hitSomething;

	if (bUsingLineTrace) {
		hitSomething = LineTrace(1000, hit);
	} else {
		hitSomething = ParabolicTrace(100, hit);
	}

	if (hitSomething) {
		if (hit.GetActor()->GetClass()->ImplementsInterface(UInteractiveObject::StaticClass())) {
			IInteractiveObject::Execute_TraceHitObject(hit.GetActor());
		}
	}
}

bool UTraceInteractionComponent::LineTrace(float Distance, FHitResult& OutHit)
{
	auto world = GetWorld();
	auto startPos = GetComponentLocation();
	auto endPos = startPos + GetForwardVector() * Distance;
	
	auto hitSomething = world->LineTraceSingleByChannel(OutHit, startPos, endPos, ECC_Visibility);

	if (hitSomething) {
		DrawDebugLine(world, startPos, OutHit.Location, FColor(128, 128, 128), false, -1.0f, 0, 2.0f);
	}

	return hitSomething;
}

bool UTraceInteractionComponent::ParabolicTrace(float Speed, FHitResult& OutHit)
{
	auto world = GetWorld();
	auto startPos = GetComponentLocation();
	auto velocity = startPos + GetForwardVector() * Speed;

	FPredictProjectilePathResult result;

	auto params = FPredictProjectilePathParams(0.01f, startPos, velocity, 0.5f);

	return false;
}

