// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActor.h"

AInteractiveActor::AInteractiveActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetMassOverrideInKg(NAME_None, Mass);
}

void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsGripped && Holder != nullptr) {
		StaticMeshComponent->SetWorldLocationAndRotation(Holder->GetComponentLocation(), Holder->GetComponentRotation());
	}
}

