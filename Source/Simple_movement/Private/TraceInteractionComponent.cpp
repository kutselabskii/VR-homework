// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework


#include "TraceInteractionComponent.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "InteractiveObject.h"
#include "UObject/ConstructorHelpers.h"

UTraceInteractionComponent::UTraceInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bUsingLineTrace = true;
}


// Called when the game starts
void UTraceInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	//static ConstructorHelpers::FObjectFinder<UClass> TeleportationBlueprint(TEXT("Blueprint'/Game/Blueprints/TeleportationVisuals.TeleportationVisuals'"));
	//auto TeleportationClass = TeleportationBlueprint.Object;

	//TeleportationVisuals = Cast<USceneComponent>(GetWorld()->SpawnActor<AActor>(TeleportationClass));
	//TeleportationVisuals->SetVisibility(false);
}


// Called every frame
void UTraceInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetRelativeLocationAndRotation(FVector(0, 0, 0), FQuat(0, 0, 0, 0));
	
	FHitResult hit;
	bool hitSomething;

	if (bUsingLineTrace) {
		hitSomething = LineTrace(1000, hit);
	} else {
		hitSomething = ParabolicTrace(1000, 0.1f, 20, hit);
	}

	InteractWithHit(hitSomething, hit);
}

void UTraceInteractionComponent::InteractWithHit(const bool HitSomething, const FHitResult& Hit)
{
	if (!HitSomething) {
		if (FocusedObject != nullptr) {
			if (FocusedObject->Implements<UInteractiveObject>()) {
				IInteractiveObject::Execute_TraceLeaveObject(FocusedObject);
				IInteractiveObject::Execute_TraceLeaveComponent(FocusedObject, FocusedComponent);
			}
			FocusedObject = nullptr;
			FocusedComponent = nullptr;
		}
		TeleportationVisuals->SetVisibility(false);
		return;
	}

	auto hitActor = Hit.Actor.Get();
	auto hitComponent = Hit.Component.Get();
	bool newImplements = hitActor->Implements<UInteractiveObject>();

	if (hitActor == FocusedObject) {
		if (newImplements) {
			IInteractiveObject::Execute_TraceMove(hitActor);
		}

		if (hitComponent != FocusedComponent) {
			if (newImplements) {
				IInteractiveObject::Execute_TraceLeaveComponent(hitActor, FocusedComponent);
				IInteractiveObject::Execute_TraceHitComponent(hitActor, hitComponent);
			}
			FocusedComponent = hitComponent;
		}
		return;
	}

	if (FocusedObject != nullptr) {
		if (FocusedObject->Implements<UInteractiveObject>()) {
			IInteractiveObject::Execute_TraceLeaveObject(FocusedObject);
		} else {
			TeleportationVisuals->SetVisibility(false);
		}
	}
	FocusedObject = nullptr;
	FocusedComponent = nullptr;

	if (newImplements) {
		IInteractiveObject::Execute_TraceHitObject(hitActor);
		IInteractiveObject::Execute_TraceHitComponent(hitActor, hitComponent);
		FocusedObject = hitActor;
		FocusedComponent = hitComponent;
	} else {
		TeleportationVisuals->SetVisibility(true);
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
	const auto velocity = GetForwardVector() * Speed;
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

void UTraceInteractionComponent::ActivateDownEvent_Implementation(const AActor* Instigator)
{
	if (FocusedObject != nullptr && FocusedObject->Implements<UInteractiveObject>()) {
		IInteractiveObject::Execute_TraceActivateDown(FocusedObject);
	}
}

void UTraceInteractionComponent::ActivateUpEvent_Implementation(const AActor* Instigator)
{
	if (FocusedObject != nullptr && FocusedObject->Implements<UInteractiveObject>()) {
		IInteractiveObject::Execute_TraceActivateUp(FocusedObject);
	}
}

