// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Minion/MinionAnimInstance.h"
#include "../Public/Character/Enemy/Minion/EnemyMinionCharacter.h"

UMinionAnimInstance::UMinionAnimInstance()
{
	curSpeed_ = 0.0f;
}

void UMinionAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	character_ = Cast<AEnemyMinionCharacter>(Pawn);

	if (::IsValid(Pawn))
	{
		curSpeed_ = Pawn->GetVelocity().Size();
		isFirstAttacking_ = character_->GetFirstAttacking();
		isSecondAttacking_ = character_->GetSecondAttacking();
		isThirdAttacking_ = character_->GetThirdAttacking();
		isInAir_ = character_->GetMovementComponent()->IsFalling();
		isHit_ = character_->GetIsHiting();
	}
}

void UMinionAnimInstance::AnimNotify_AttackFirEnd()
{
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}
	character_->onFirstAttack_.Broadcast(false);
}

void UMinionAnimInstance::AnimNotify_AttackSecEnd()
{
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}
	character_->onSecondAttack_.Broadcast(false);
}

void UMinionAnimInstance::AnimNotify_AttackThiEnd()
{
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}
	character_->onThirdAttack_.Broadcast(false);
}

void UMinionAnimInstance::AnimNotify_HitEnd()
{
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}
	ABLOG(Warning, TEXT("Minion Anim Hit"));
	character_->onHit_.Broadcast(false);
}
