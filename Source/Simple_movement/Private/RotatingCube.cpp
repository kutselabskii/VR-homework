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
}

void ARotatingCube::BeginPlay()
{
    Super::BeginPlay();

	SetActorScale3D(FVector(1.0f, 2.0f, 1.0f));
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

void ARotatingCube::TraceActivateDown_Implementation()
{
    isRotating = false;
}

void ARotatingCube::TraceActivateUp_Implementation()
{
    isRotating = true;
}