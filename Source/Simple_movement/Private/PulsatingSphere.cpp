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
        auto value = FMath::InterpSinIn(0.01f, 1.0f, FMath::Sin(seconds));

        SetActorScale3D(FVector(value, value, value));
    }
}

void APulsatingSphere::TraceHitObject_Implementation()
{

}

void APulsatingSphere::TraceLeaveObject_Implementation()
{
    ShouldPulse = true;
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

void APulsatingSphere::TraceActivateDown_Implementation()
{
    ShouldPulse = false;
}

void APulsatingSphere::TraceActivateUp_Implementation()
{
    ShouldPulse = true;
}

void APulsatingSphere::SetColor()
{
    //UMaterialInstanceDynamic* dynamicMaterial = UMaterialInstanceDynamic::Create(StaticMeshComponent->GetMaterial(0), StaticMeshComponent);
    //StaticMeshComponent->SetMaterial(0, dynamicMaterial);

    float Saturation = (float)ColorSaturation / 255;
    FLinearColor Color = FLinearColor(
        ((ActiveColors & (uint8)ESphereColors::Red) != (uint8)ESphereColors::None) * Saturation,
        ((ActiveColors & (uint8)ESphereColors::Green) != (uint8)ESphereColors::None) * Saturation,
        ((ActiveColors & (uint8)ESphereColors::Blue) != (uint8)ESphereColors::None) * Saturation,
        1.0f);
    //dynamicMaterial->SetVectorParameterValue(TEXT("Color"), Color);

    StaticMeshComponent->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(Color));
}