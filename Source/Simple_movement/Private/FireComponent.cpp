// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework


#include "FireComponent.h"
#include "UObject/ConstructorHelpers.h"

UFireComponent::UFireComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FireComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticleSystem"));
	SteamComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SteamParticleSystem"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> FireAsset(TEXT("ParticleSystem'/Game/Particles/PS_Fire.PS_Fire'"));
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> SteamAsset(TEXT("ParticleSystem'/Game/Particles/PS_Fire.PS_Fire'"));

	if (FireAsset.Succeeded()) {
		FireComponent->SetTemplate(FireAsset.Object);
	}

	auto strictRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	FireComponent->AttachToComponent(this, strictRules);

	SetRelativeLocation(FVector(0, 0, 0));
}

void UFireComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bSelfIgnition) {
		FireComponent->ActivateSystem();
	} else {
		FireComponent->DeactivateSystem();
	}
}

void UFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetRelativeLocation(FVector(0, 0, 0));
}

