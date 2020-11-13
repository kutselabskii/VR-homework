// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "FireComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLE_MOVEMENT_API UFireComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UParticleSystemComponent* FireComponent;
	UParticleSystemComponent* SteamComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSelfIgnition = false;

	UFireComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
