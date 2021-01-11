// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/ADAnimInstance.h"
#include "../Public/Character/Enemy/ADEnemyCharacter.h"

UADAnimInstance::UADAnimInstance()
{
	curSpeed_ = 0.0f;
	isDead_ = false;
}

void UADAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (::IsValid(Pawn))
	{
		curSpeed_ = Pawn->GetVelocity().Size();
		//ABLOG(Warning, TEXT("%f"), curSpeed_);
	}
}

void UADAnimInstance::SetDeadAnim()
{
	isDead_ = true;
}

void UADAnimInstance::AnimNotify_DieEnd()
{
	auto Pawn = TryGetPawnOwner();
	auto Character = Cast<AADEnemyCharacter>(Pawn);

	if (::IsValid(Pawn) && Character != nullptr)
	{
		Character->EnemyDestroy();
	}
}