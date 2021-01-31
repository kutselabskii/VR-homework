// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework


#include "TraceInteractionComponent.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "InteractiveObject.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"

UTraceInteractionComponent::UTraceInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TeleportationVisuals = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TeleportationVisualsAsset(TEXT("/Engine/BasicShapes/Plane.Plane"));
	static ConstructorHelpers::FObjectFinder<UMaterial> TeleportationVisualsMaterial(TEXT("Material'/Game/Materials/TeleportTexture.TeleportTexture'"));

	if (TeleportationVisualsAsset.Succeeded())
	{
		TeleportationVisuals->SetStaticMesh(TeleportationVisualsAsset.Object);
		TeleportationVisuals->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (TeleportationVisualsMaterial.Succeeded()) {
		TeleportationVisuals->SetMaterial(0, TeleportationVisualsMaterial.Object);
	}

	UsingLineTrace = false;
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

	SetRelativeLocationAndRotation(FVector(0, 0, 0), FQuat(0, 0, 0, 0));
	
	if (State == ControllerState::Idle) {
		FHitResult hit;
		bool hitSomething;

		if (UsingLineTrace) {
			hitSomething = LineTrace(1000, hit);
		}
		else {
			hitSomething = ParabolicTrace(1000, 0.1f, 20, hit);
		}

		InteractWithHit(hitSomething, hit);
	}
}

void UTraceInteractionComponent::InteractWithHit(const bool HitSomething, const FHitResult& Hit)
{
	if (!HitSomething) {
		NoHitOccured();
		return;
	}

	auto hitActor = Hit.Actor.Get();
	if (hitActor == FocusedObject) {
		HitSameThing(Hit);
		return;
	}

	HitOtherThing(Hit);
}

void UTraceInteractionComponent::NoHitOccured()
{
	if (FocusedObject != nullptr) {
		if (FocusedObject->Implements<UInteractiveObject>()) {
			IInteractiveObject::Execute_TraceLeaveObject(FocusedObject);
			IInteractiveObject::Execute_TraceLeaveComponent(FocusedObject, FocusedComponent);
		}
		FocusedObject = nullptr;
		FocusedComponent = nullptr;
	}
	TeleportationVisuals->SetVisibility(false);
}

void UTraceInteractionComponent::HitSameThing(const FHitResult& Hit)
{
	auto hitActor = Hit.Actor.Get();
	auto hitComponent = Hit.Component.Get();
	bool newImplements = hitActor->Implements<UInteractiveObject>();

	if (newImplements) {
		IInteractiveObject::Execute_TraceMove(hitActor);
	}
	else {
		TeleportationVisuals->SetWorldLocation(Hit.Location + FVector(0, 0, 0.01f));
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

void UTraceInteractionComponent::HitOtherThing(const FHitResult& Hit)
{
	auto hitActor = Hit.Actor.Get();
	auto hitComponent = Hit.Component.Get();
	bool newImplements = hitActor->Implements<UInteractiveObject>();

	if (FocusedObject != nullptr) {
		if (FocusedObject->Implements<UInteractiveObject>()) {
			IInteractiveObject::Execute_TraceLeaveObject(FocusedObject);
		}

		TeleportationVisuals->SetVisibility(false);
	}
	FocusedObject = nullptr;
	FocusedComponent = nullptr;

	if (newImplements) {
		IInteractiveObject::Execute_TraceHitObject(hitActor);
		IInteractiveObject::Execute_TraceHitComponent(hitActor, hitComponent);
	}
	else {
		TeleportationVisuals->SetVisibility(true);
		TeleportationVisuals->SetWorldLocation(Hit.Location);
	}

	FocusedObject = hitActor;
	FocusedComponent = hitComponent;
}

bool UTraceInteractionComponent::LineTrace(const float Distance, FHitResult& OutHit)
{
	const auto world = GetWorld();
	const auto startPos = GetComponentLocation();
	const auto endPos = startPos + GetForwardVector() * Distance;
	
	auto hitSomething = world->LineTraceSingleByChannel(OutHit, startPos, endPos, ECC_Visibility);

	if (hitSomething) {
		auto color = OutHit.Actor.Get()->Implements<UInteractiveObject>() ? InteractiveTraceColor : NonInteractiveTraceColor;
		DrawDebugLine(world, startPos, OutHit.Location, color, false, -1.0f, 0, 2.0f);
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

			auto color = OutHit.Actor.Get()->Implements<UInteractiveObject>() ? InteractiveTraceColor : NonInteractiveTraceColor;
			for (int j = 1; j < points.Num(); ++j) {
				DrawDebugLine(world, points[j - 1], points[j], color, false, -1.0f, 0, 2.0f);
			}

			return true;
		}

		previousLocation = endingLocation;
		points.Add(endingLocation);
	}
	
	return false;
}

void UTraceInteractionComponent::TriggerDownEvent_Implementation(AActor* Instigator)
{
	if (FocusedObject != nullptr) {
		if (FocusedObject->Implements<UInteractiveObject>()) {
			IInteractiveObject::Execute_TraceTriggerDown(FocusedObject);
		}
	}
}

void UTraceInteractionComponent::TriggerUpEvent_Implementation(AActor* Instigator)
{
	if (FocusedObject != nullptr) {
		if (FocusedObject->Implements<UInteractiveObject>()) {
			IInteractiveObject::Execute_TraceTriggerUp(FocusedObject);
		} else {
			TeleportPlayer(Instigator, TeleportationVisuals->GetComponentLocation());
		}
	}
}

void UTraceInteractionComponent::GripDownEvent_Implementation(AActor* Instigator)
{
	State = ControllerState::Grip;
	TeleportationVisuals->SetVisibility(false);

	if (FocusedObject != nullptr && FocusedObject->Implements<UInteractiveObject>()) {
		IInteractiveObject::Execute_TraceGripDown(FocusedObject, GetAttachParent());
	}
}

void UTraceInteractionComponent::GripUpEvent_Implementation(AActor* Instigator)
{
	State = ControllerState::Idle;
	TeleportationVisuals->SetVisibility(true);

	if (FocusedObject != nullptr && FocusedObject->Implements<UInteractiveObject>()) {
		IInteractiveObject::Execute_TraceGripUp(FocusedObject, GetAttachParent());
	}
}

void UTraceInteractionComponent::TeleportPlayer(AActor* Player, const FVector& Location)
{
	// Player->SetActorLocation(FVector(Location.X, Location.Y, Player->GetActorLocation().Z));
	Player->SetActorLocation(FVector(Location.X, Location.Y, Location.Z + PlayerHeight));
}

