// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "InteractiveActor.generated.h"

UCLASS(Abstract, Blueprintable)
class SIMPLE_MOVEMENT_API AInteractiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractiveActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Mass = 500.0f;

protected:
	USceneComponent* Holder = nullptr;
	bool IsGripped = false;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void Hold(USceneComponent* Object);

	UFUNCTION(BlueprintCallable)
	virtual void Drop();
};
