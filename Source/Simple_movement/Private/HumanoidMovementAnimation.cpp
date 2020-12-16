// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework

#include "HumanoidMovementAnimation.h"
#include "GameFramework/PawnMovementComponent.h"

void UHumanoidMovementAnimation::UpdateAnimationProperties()
{
	APawn* Pawn = TryGetPawnOwner();

	if (Pawn) {
		bIsFalling = Pawn->GetMovementComponent()->IsFalling();

		MovementSpeed = Pawn->GetVelocity().Size();
	}
}