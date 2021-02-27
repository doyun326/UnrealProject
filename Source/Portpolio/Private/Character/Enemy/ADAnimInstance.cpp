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
	character_ = Cast<AADEnemyCharacter>(Pawn);

	if (Pawn == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Pawn"));
		return;
	}

	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : ADEnemyCharacter"));
		return;
	}

	if (::IsValid(Pawn))
	{
		isFirstAttacking_ = character_->GetFirstAttacking();
		isSecondAttacking_ = character_->GetSecondAttacking();
		isHit_ = character_->GetIsHiting();
		curSpeed_ = Pawn->GetVelocity().Size();
		//ABLOG(Warning, TEXT("%f"), curSpeed_);
	}
}

void UADAnimInstance::AnimNotify_AttackFirEnd()
{
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}
	character_->onFirstAttack_.Broadcast(false);
}

void UADAnimInstance::AnimNotify_AttackSecEnd()
{
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}
	character_->onSecondAttack_.Broadcast(false);
}

void UADAnimInstance::AnimNotify_AttackHitCheck()
{
	onAttackHitCheck_.Broadcast();
}

void UADAnimInstance::AnimNotify_HitEnd()
{
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}
	character_->onHit_.Broadcast(false);
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