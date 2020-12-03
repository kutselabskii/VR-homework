// Egor Kutselabskii 2020-... No rights reserved, please do not copy my homework


#include "GameFramework/PawnMovementComponent.h"
#include "HumanoidMovementAnimation.h"

void UHumanoidMovementAnimation::UpdateAnimationProperties()
{
	APawn* Pawn = TryGetPawnOwner();

	if (Pawn) {
		bIsFalling = Pawn->GetMovementComponent()->IsFalling();

		MovementSpeed = Pawn->GetVelocity().Size();
	}
}