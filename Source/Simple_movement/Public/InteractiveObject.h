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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TraceHitObject();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TraceLeaveObject();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TraceHitComponent(UPrimitiveComponent* Component);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TraceLeaveComponent(UPrimitiveComponent* Component);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TraceMove();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TraceTriggerDown();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TraceTriggerUp();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TraceGripDown(USceneComponent* Object);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TraceGripUp(USceneComponent* Object);
};
