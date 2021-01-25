// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BossAnimInstance.h"

UBossAnimInstance::UBossAnimInstance()
{

}

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (::IsValid(Pawn))
	{
		curSpeed_ = Pawn->GetVelocity().Size();
		//ABLOG(Warning, TEXT("%f"), curSpeed_);
	}
}