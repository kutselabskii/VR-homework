// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "PulsatingSphere.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_MOVEMENT_API APulsatingSphere : public AInteractiveActor
{
	GENERATED_BODY()
	
public:
	APulsatingSphere();
	void Tick(float DeltaTime) override;

protected:
	void BeginPlay() override;
};
