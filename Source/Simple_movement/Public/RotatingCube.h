// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "InteractiveObject.h"
#include "RotatingCube.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_MOVEMENT_API ARotatingCube : public AInteractiveActor, public IInteractiveObject
{
	GENERATED_BODY()
	
public:
	ARotatingCube();
	void Tick(float DeltaTime) override;

	void Selected_Implementation() override;

	void Activated_Implementation() override;

protected:
	void BeginPlay() override;

private:
	bool isRotating = true;
};
