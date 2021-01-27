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
		//isFirstAttacking_ = character_->GetAttacking();
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
	character_->OnAttackFirEnd.Broadcast();
}

void UBossAnimInstance::AnimNotify_AttackSecEnd()
{
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}
	character_->OnAttackSecEnd.Broadcast();
}

void UBossAnimInstance::AnimNotify_AttackThiEnd()
{
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}
	character_->OnAttackThiEnd.Broadcast();
}