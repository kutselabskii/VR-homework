// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework


#include "PulsatingSphere.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

APulsatingSphere::APulsatingSphere() : Super::AInteractiveActor()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/Meshes/BaseSphereMesh"));

    if (SphereVisualAsset.Succeeded())
    {
        StaticMeshComponent->SetStaticMesh(SphereVisualAsset.Object);
    }

    Mass = 250.0f;

    SetActorScale3D(FVector(0.3f, 0.3f, 0.3f));
}

void APulsatingSphere::BeginPlay()
{
    Super::BeginPlay();

    SetColor();
}

void APulsatingSphere::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    SetColor();
}

void APulsatingSphere::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (ShouldPulse) {
        auto seconds = GetWorld()->GetRealTimeSeconds();
        auto value = FMath::InterpSinIn(0.2f, 0.5f, FMath::Sin(seconds));

        SetActorScale3D(FVector(value, value, value));
    }

    UpdateSnow(DeltaTime);
}

void APulsatingSphere::TraceHitObject_Implementation()
{
 
}

void APulsatingSphere::TraceLeaveObject_Implementation()
{
    ShouldPulse = false;
}

void APulsatingSphere::TraceHitComponent_Implementation(UPrimitiveComponent* Component)
{

}

void APulsatingSphere::TraceLeaveComponent_Implementation(UPrimitiveComponent* Component)
{

}

void APulsatingSphere::TraceMove_Implementation()
{

}

void APulsatingSphere::TraceTriggerDown_Implementation()
{
    ShouldPulse = true;
}

void APulsatingSphere::TraceTriggerUp_Implementation()
{
    ShouldPulse = false;
}

void APulsatingSphere::TraceGripDown_Implementation(USceneComponent* Object)
{
    if (FVector::Dist(Object->GetComponentLocation(), GetActorLocation()) < 150.0f) {
        Hold(Object);
    }
}

void APulsatingSphere::TraceGripUp_Implementation(USceneComponent* Object)
{
    Drop();
}

void APulsatingSphere::SetColor()
{
    float Saturation = (float)ColorSaturation / 255;
    FLinearColor Color = FLinearColor(
        ((ActiveColors & (uint8)ESphereColors::Red) != (uint8)ESphereColors::None) * Saturation,
        ((ActiveColors & (uint8)ESphereColors::Green) != (uint8)ESphereColors::None) * Saturation,
        ((ActiveColors & (uint8)ESphereColors::Blue) != (uint8)ESphereColors::None) * Saturation,
        1.0f);

    StaticMeshComponent->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(Color));
}

void APulsatingSphere::UpdateSnow(float DeltaTime)
{
    if (GetVelocity().Size() > 0) {
        SnowLevel -= 2.0f * DeltaTime;
    } else {
        SnowLevel += 1.1f * DeltaTime;
    }

    SnowLevel = FMath::Clamp(SnowLevel, -10.0f, 50.0f);

    StaticMeshComponent->SetScalarParameterValueOnMaterials(TEXT("SnowBias"), SnowLevel);
}