// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "FireComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLE_MOVEMENT_API UFireComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* FireComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* SteamComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSelfIgnition = false;

	//UFUNCTION()
	//void ParticleCollide(FName EventName, float EmitterTime, int32 ParticleTime, FVector Location, FVector Velocity, FVector Direction, FVector Normal, FName BoneName, UPhysicalMaterial* PhysMat);

	UFireComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
