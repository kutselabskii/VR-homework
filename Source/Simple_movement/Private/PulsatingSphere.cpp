// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework


#include "PulsatingSphere.h"
#include "UObject/ConstructorHelpers.h"

APulsatingSphere::APulsatingSphere() : Super::AInteractiveActor()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/Meshes/BaseSphereMesh"));

    if (CubeVisualAsset.Succeeded())
    {
        StaticMeshComponent->SetStaticMesh(CubeVisualAsset.Object);
    }
}

void APulsatingSphere::BeginPlay()
{
    Super::BeginPlay();
}

void APulsatingSphere::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto seconds = GetWorld()->GetRealTimeSeconds();
    auto value = FMath::InterpSinIn(0.01f, 1.0f, FMath::Sin(seconds));

    SetActorScale3D(FVector(value, value, value));
}

void APulsatingSphere::TraceHitObject_Implementation()
{

}

void APulsatingSphere::TraceLeaveObject_Implementation()
{
    
}

void APulsatingSphere::TraceHitComponent_Implementation()
{

}

void APulsatingSphere::TraceLeaveComponent_Implementation()
{

}

void APulsatingSphere::TraceMove_Implementation()
{

}

void APulsatingSphere::TraceActivateDown_Implementation()
{

}

void APulsatingSphere::TraceActivateUp_Implementation()
{

}