// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework


#include "MagicWand.h"

AMagicWand::AMagicWand() : Super::AInteractiveActor()
{
    Mass = 2000.0f;

    Spell = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    auto strictRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
    //Spell->AttachToComponent(RootComponent, strictRules);

    Spell->SetupAttachment(RootComponent);
}

void AMagicWand::BeginPlay()
{
    Super::BeginPlay();
}

void AMagicWand::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMagicWand::TraceHitObject_Implementation()
{

}

void AMagicWand::TraceLeaveObject_Implementation()
{

}

void AMagicWand::TraceHitComponent_Implementation(UPrimitiveComponent* Component)
{

}

void AMagicWand::TraceLeaveComponent_Implementation(UPrimitiveComponent* Component)
{

}

void AMagicWand::TraceMove_Implementation()
{

}

void AMagicWand::TraceTriggerDown_Implementation()
{
    if (IsGripped) {
        Spell->ActivateSystem();
    }
}

void AMagicWand::TraceTriggerUp_Implementation()
{

}

void AMagicWand::TraceGripDown_Implementation(USceneComponent* Object)
{
    if (FVector::Dist(Object->GetComponentLocation(), GetActorLocation()) < 150.0f) {
        IsGripped = true;
        Holder = Object;
        StaticMeshComponent->SetEnableGravity(false);
    }
}

void AMagicWand::TraceGripUp_Implementation(USceneComponent* Object)
{
    IsGripped = false;
    Holder = nullptr;
    StaticMeshComponent->SetEnableGravity(true);
}
