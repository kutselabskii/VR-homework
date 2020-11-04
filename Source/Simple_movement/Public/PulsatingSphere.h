// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "InteractiveObject.h"
#include "PulsatingSphere.generated.h"


UENUM(Blueprintable, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ESphereColors : uint8
{
	None = 0 UMETA(Hidden),
	Red = 1 << 0,
	Green = 1 << 1,
	Blue = 1 << 2
};

/**
 * 
 */
UCLASS()
class SIMPLE_MOVEMENT_API APulsatingSphere : public AInteractiveActor, public IInteractiveObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ESphereColors"))
	uint8 ActiveColors;

	UPROPERTY(EditAnywhere, meta = (UIMin = 0, UIMax = 255))
	uint8 ColorSaturation = 255;

	APulsatingSphere();
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

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	void BeginPlay() override;

private:
	bool ShouldPulse = false;
	float SnowLevel = -10.0f;

	void SetColor();
	void UpdateSnow(float DeltaTime);
};
