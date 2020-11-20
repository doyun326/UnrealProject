// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	currentChrSpeed_ = 0.0f;

	//구르기 모션 가져오기
	static ConstructorHelpers::FObjectFinder<UAnimMontage> JUMP_MONTAGE(TEXT("/Game/My/Blueprints/Anim/Character/Player/DiveJump_MT.DiveJump_MT"));

	if (JUMP_MONTAGE.Succeeded())
	{
		diveMontage_ = JUMP_MONTAGE.Object;
	}
}

//Pawn Speed 사용
void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (::IsValid(Pawn))
	{
		currentChrSpeed_ = Pawn->GetVelocity().Size();
		ABLOG(Warning, TEXT("Speed : %f"), currentChrSpeed_);
	}
}

//DiveJump Montage
void UPlayerAnimInstance::PlayDiveJumpMontage()
{
	if (!Montage_IsPlaying(diveMontage_))
	{
		Montage_Play(diveMontage_, 2.0f);
	}
}