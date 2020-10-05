// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "RotatingCube.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_MOVEMENT_API ARotatingCube : public AInteractiveActor
{
	GENERATED_BODY()
	
public:
	ARotatingCube();

	void BeginPlay() override;
};
