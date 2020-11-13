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
}

void UFireComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bSelfIgnition) {
		FireComponent->ActivateSystem();
	}
}

void UFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetRelativeLocationAndRotation(FVector(0, 0, 50), FQuat(0, 0, 0, 0));
}

