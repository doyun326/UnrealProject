// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "WarPlayerController.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	currentChrSpeed_ = 0.0f;
	isFire_ = false;

	//������ ��� ��������
	static ConstructorHelpers::FObjectFinder<UAnimMontage> JUMP_MONTAGE(TEXT("/Game/My/Blueprints/Anim/Character/Player/DiveJump_MT.DiveJump_MT"));

	if (JUMP_MONTAGE.Succeeded())
	{
		diveMontage_ = JUMP_MONTAGE.Object;
	}
}

//Pawn Speed ���
void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	auto Character = Cast<APlayerCharacter>(Pawn);

	if (::IsValid(Pawn))
	{
		currentChrSpeed_ = Pawn->GetVelocity().Size();
		isFire_ = Character->GetIsShooting();
	}

	ABLOG(Warning, TEXT("Speed : %f"), currentChrSpeed_);
}

//DiveJump Montage
void UPlayerAnimInstance::PlayDiveJumpMontage()
{
	if (!Montage_IsPlaying(diveMontage_))
	{
		Montage_Play(diveMontage_, 2.5f);
	}
}

//Fire Gun Montage
void UPlayerAnimInstance::PlayFireGunMontage()
{
	if (!Montage_IsPlaying(fireMontage_))
	{
		//Montage_Play(fireMontage_, 2.0f);
	}
}