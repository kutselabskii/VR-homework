// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "InteractiveObject.h"
#include "PulsatingSphere.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_MOVEMENT_API APulsatingSphere : public AInteractiveActor, public IInteractiveObject
{
	GENERATED_BODY()
	
public:
	APulsatingSphere();
	void Tick(float DeltaTime) override;

	void TraceHitObject_Implementation() override;

	void TraceLeaveObject_Implementation() override;

	void TraceHitComponent_Implementation(UPrimitiveComponent* Component) override;

	void TraceLeaveComponent_Implementation(UPrimitiveComponent* Component) override;

	void TraceMove_Implementation() override;

	void TraceActivateDown_Implementation() override;

	void TraceActivateUp_Implementation() override;

protected:
	void BeginPlay() override;
};
