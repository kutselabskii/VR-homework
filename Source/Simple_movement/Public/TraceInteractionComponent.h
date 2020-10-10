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

protected:
	virtual void BeginPlay() override;

	virtual bool LineTrace(float Distance, FHitResult& OutHit);
	virtual bool ParabolicTrace(float Speed, FHitResult& OutHit);
};
