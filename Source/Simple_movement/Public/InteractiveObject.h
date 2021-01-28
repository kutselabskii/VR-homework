// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractiveObject.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UInteractiveObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLE_MOVEMENT_API IInteractiveObject
{
	GENERATED_BODY()

public:
	UFUNCTION(Blueprintable, BlueprintCallable, BlueprintNativeEvent)
	void TraceHitObject();

	UFUNCTION(Blueprintable, BlueprintCallable, BlueprintNativeEvent)
	void TraceLeaveObject();

	UFUNCTION(Blueprintable, BlueprintCallable, BlueprintNativeEvent)
	void TraceHitComponent(UPrimitiveComponent* Component);

	UFUNCTION(Blueprintable, BlueprintCallable, BlueprintNativeEvent)
	void TraceLeaveComponent(UPrimitiveComponent* Component);

	UFUNCTION(Blueprintable, BlueprintCallable, BlueprintNativeEvent)
	void TraceMove();

	UFUNCTION(Blueprintable, BlueprintCallable, BlueprintNativeEvent)
	void TraceTriggerDown();

	UFUNCTION(Blueprintable, BlueprintCallable, BlueprintNativeEvent)
	void TraceTriggerUp();

	UFUNCTION(Blueprintable, BlueprintCallable, BlueprintNativeEvent)
	void TraceGripDown(USceneComponent* Object);

	UFUNCTION(Blueprintable, BlueprintCallable, BlueprintNativeEvent)
	void TraceGripUp(USceneComponent* Object);
};
