// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BossAnimInstance.h"
#include "../Public/Character/Enemy/Boss/BossCharacter.h"

UBossAnimInstance::UBossAnimInstance()
{
	curSpeed_ = 0.0f;
	isAttacking_ = false;
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
		isAttacking_ = character_->GetAttacking();
		//ABLOG(Warning, TEXT("%f"), curSpeed_);
		//ABLOG(Warning, TEXT("%d"), isAttacking_);
	}
}

void UBossAnimInstance::AnimNotify_AttackEnd()
{
	ABLOG(Warning, TEXT("AttackEnd"));
	if (character_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Character"));
		return;
	}

	character_->OnAttackEnd.Broadcast();
}