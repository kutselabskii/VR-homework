// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TraceInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLE_MOVEMENT_API UTraceInteractionComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	bool bUsingLineTrace;

	UTraceInteractionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActivateDownEvent(const AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActivateUpEvent(const AActor* Instigator);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* TeleportationVisuals;

protected:
	AActor* FocusedObject;
	UPrimitiveComponent* FocusedComponent;

	virtual void BeginPlay() override;

	virtual bool LineTrace(const float Distance, FHitResult& OutHit);
	virtual bool ParabolicTrace(const float Speed, const float TimeStep, const int Segments, FHitResult& OutHit);
	virtual void InteractWithHit(const bool HitSomething, const FHitResult& Hit);
};
