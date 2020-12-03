// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HumanoidMovementAnimation.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_MOVEMENT_API UHumanoidMovementAnimation : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed;

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties();
};
