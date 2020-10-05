// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework


#include "RotatingCube.h"
#include "UObject/ConstructorHelpers.h"

ARotatingCube::ARotatingCube() : Super::AInteractiveActor()
{
    ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/Content/Meshes/BaseCubeMesh"));

    if (CubeVisualAsset.Succeeded())
    {
        StaticMeshComponent->SetStaticMesh(CubeVisualAsset.Object);
    }
}

void ARotatingCube::BeginPlay()
{
    

	SetActorScale3D(FVector(1.0f, 1.0f, 2.0f));
}