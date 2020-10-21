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

	void TraceHitObject_Implementation() override;
	void TraceLeaveObject_Implementation() override;
	void TraceHitComponent_Implementation(UPrimitiveComponent* Component) override;
	void TraceLeaveComponent_Implementation(UPrimitiveComponent* Component) override;
	void TraceMove_Implementation() override;
	void TraceTriggerDown_Implementation() override;
	void TraceTriggerUp_Implementation() override;
	void TraceGripDown_Implementation(USceneComponent* Object) override;
	void TraceGripUp_Implementation(USceneComponent* Object) override;

protected:
	void BeginPlay() override;

private:
	bool isRotating = false;
};
