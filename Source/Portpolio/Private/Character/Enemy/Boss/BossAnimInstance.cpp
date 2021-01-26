// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BossAnimInstance.h"
#include "../Public/Character/Enemy/Boss/BossCharacter.h"

UBossAnimInstance::UBossAnimInstance()
{

}

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	auto Character = Cast<ABossCharacter>(Pawn);

	if (::IsValid(Pawn))
	{
		curSpeed_ = Pawn->GetVelocity().Size();
		//ABLOG(Warning, TEXT("%f"), curSpeed_);
	}
}