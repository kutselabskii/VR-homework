// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TraceInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLE_MOVEMENT_API UTraceInteractionComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool UsingLineTrace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TeleportationVisuals;

	FColor InteractiveTraceColor = FColor(255, 128, 128);
	FColor NonInteractiveTraceColor = FColor(128, 128, 128);

	UTraceInteractionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActivateDownEvent(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActivateUpEvent(AActor* Instigator);

protected:
	AActor* FocusedObject;
	UPrimitiveComponent* FocusedComponent;

	virtual void BeginPlay() override;

	virtual bool LineTrace(const float Distance, FHitResult& OutHit);
	virtual bool ParabolicTrace(const float Speed, const float TimeStep, const int Segments, FHitResult& OutHit);
	virtual void InteractWithHit(const bool HitSomething, const FHitResult& Hit);

	virtual void TeleportPlayer(AActor* Player, const FVector& Location);

private:
	void NoHitOccured();
	void HitSameThing(const FHitResult& Hit);
	void HitOtherThing(const FHitResult& Hit);
};
