// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractiveObject.generated.h"

// This class does not need to be modified.
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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Selected();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Activated();
};
