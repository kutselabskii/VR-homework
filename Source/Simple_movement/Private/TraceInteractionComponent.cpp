// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework


#include "TraceInteractionComponent.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "InteractiveObject.h"

UTraceInteractionComponent::UTraceInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bUsingLineTrace = false;
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
		hitSomething = ParabolicTrace(1000, 0.05f, 20, hit);
	}

	if (hitSomething) {
		if (hit.GetActor()->GetClass()->ImplementsInterface(UInteractiveObject::StaticClass())) {
			IInteractiveObject::Execute_TraceHitObject(hit.GetActor());
		}
	}
}

bool UTraceInteractionComponent::LineTrace(const float Distance, FHitResult& OutHit)
{
	const auto world = GetWorld();
	const auto startPos = GetComponentLocation();
	const auto endPos = startPos + GetForwardVector() * Distance;
	
	auto hitSomething = world->LineTraceSingleByChannel(OutHit, startPos, endPos, ECC_Visibility);

	if (hitSomething) {
		DrawDebugLine(world, startPos, OutHit.Location, FColor(128, 128, 128), false, -1.0f, 0, 2.0f);
	}

	return hitSomething;
}

bool UTraceInteractionComponent::ParabolicTrace(const float Speed, const float TimeStep, const int Segments, FHitResult& OutHit)
{
	const auto world = GetWorld();
	const auto startPos = GetComponentLocation();
	const auto velocity = startPos + GetForwardVector() * Speed;
	const auto initialLocation = GetComponentLocation();
	auto previousLocation = initialLocation;
	
	TArray<FVector> points({ initialLocation });
	for (int i = 0; i < Segments; ++i) {
		const auto step = TimeStep * i;
		const auto stepLocation = velocity * step;
		const auto endingLocation = FVector(stepLocation.X, stepLocation.Y, stepLocation.Z - (double)step * step * 0.5 * 980) + initialLocation;

		auto hitSomething = world->LineTraceSingleByChannel(OutHit, previousLocation, endingLocation, ECC_Visibility);
		if (hitSomething) {
			points.Add(OutHit.Location);

			for (int j = 1; j < points.Num(); ++j) {
				DrawDebugLine(world, points[j - 1], points[j], FColor(128, 128, 128), false, -1.0f, 0, 2.0f);
			}

			return true;
		}

		previousLocation = endingLocation;
		points.Add(endingLocation);
	}
	
	return false;
}

