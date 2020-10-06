// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActor.h"

AInteractiveActor::AInteractiveActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
}

void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

