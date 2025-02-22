// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BossAnimInstance.h"
#include "../Public/Character/Enemy/Boss/BossCharacter.h"

UBossAnimInstance::UBossAnimInstance()
{
	curSpeed_ = 0.0f;
	isInAir_ = false;
	isFirstAttacking_ = false;
	isSecondAttacking_ = false;
	isThirdAttacking_ = false;
	isHit_ = false;
}

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	character_ = Cast<ABossCharacter>(Pawn);

	if (Pawn == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Pawn"));
		return;
	}

	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}

	if (::IsValid(Pawn))
	{
		curSpeed_ = Pawn->GetVelocity().Size();
		isFirstAttacking_ = character_->GetFirstAttacking();
		isSecondAttacking_ = character_->GetSecondAttacking();
		isThirdAttacking_ = character_->GetThirdAttacking();
		isInAir_ = character_->GetMovementComponent()->IsFalling();
		isHit_ = character_->GetIsHiting();
		//ABLOG(Warning, TEXT("%f"), curSpeed_);
		//ABLOG(Warning, TEXT("%d"), isAttacking_);
	}
}

void UBossAnimInstance::AnimNotify_AttackFirEnd()
{
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}
	character_->onFirstAttack_.Broadcast(false);
}

void UBossAnimInstance::AnimNotify_AttackSecEnd()
{
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}
	character_->onSecondAttack_.Broadcast(false);
}

void UBossAnimInstance::AnimNotify_AttackThiEnd()
{
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}
	character_->onThirdAttack_.Broadcast(false);
}

void UBossAnimInstance::AnimNotify_HitEnd()
{
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}
	character_->onHit_.Broadcast(false);
}

void UBossAnimInstance::SetDeadAnim()
{
	isDead_ = true;
}

void UBossAnimInstance::AnimNotify_DieEnd()
{
	onDieEnd_.Broadcast();
}