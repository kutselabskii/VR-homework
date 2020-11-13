// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework


#include "RotatingCube.h"
#include "UObject/ConstructorHelpers.h"

ARotatingCube::ARotatingCube() : Super::AInteractiveActor()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/Meshes/BaseCubeMesh"));

    if (CubeVisualAsset.Succeeded())
    {
        StaticMeshComponent->SetStaticMesh(CubeVisualAsset.Object);
    }

    Mass = 2000.0f;

    FireComponent = CreateDefaultSubobject<UFireComponent>(TEXT("FireComponent"));
}

void ARotatingCube::BeginPlay()
{
    Super::BeginPlay();
}

void ARotatingCube::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (isRotating) {
        AddActorWorldRotation(FRotator(40 * DeltaTime, 150 * DeltaTime, 75 * DeltaTime));
    }
}

void ARotatingCube::TraceHitObject_Implementation()
{

}

void ARotatingCube::TraceLeaveObject_Implementation()
{
    isRotating = false;
}

void ARotatingCube::TraceHitComponent_Implementation(UPrimitiveComponent* Component)
{

}

void ARotatingCube::TraceLeaveComponent_Implementation(UPrimitiveComponent* Component)
{

}

void ARotatingCube::TraceMove_Implementation()
{

}

void ARotatingCube::TraceTriggerDown_Implementation()
{
    isRotating = true;
}

void ARotatingCube::TraceTriggerUp_Implementation()
{
    isRotating = false;
}

void ARotatingCube::TraceGripDown_Implementation(USceneComponent* Object)
{
    if (FVector::Dist(Object->GetComponentLocation(), GetActorLocation()) < 150.0f) {
        IsGripped = true;
        Holder = Object;
        StaticMeshComponent->SetEnableGravity(false);
    }
}

void ARotatingCube::TraceGripUp_Implementation(USceneComponent* Object)
{
    IsGripped = false;
    Holder = nullptr;
    StaticMeshComponent->SetEnableGravity(true);
}