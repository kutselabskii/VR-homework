// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "InteractiveObject.h"
#include "PulsatingSphere.generated.h"


UENUM(BlueprintType, meta=(Bitflags))
enum class SphereColors: uint8
{
	None = 0,
	Red = 1 UMETA(DisplayName = "Red"),
	Green = 2 UMETA(DisplayName = "Green"),
	Blue = 4 UMETA(DisplayName = "Blue"),
};
ENUM_CLASS_FLAGS( SphereColors )

/**
 * 
 */
UCLASS()
class SIMPLE_MOVEMENT_API APulsatingSphere : public AInteractiveActor, public IInteractiveObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = SphereColors))
	uint8 ActiveColors;

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
