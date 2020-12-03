// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GunWeapon.h"
#include "WarPlayerController.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{	
	currentChrSpeed_ = 0.0f;
	isFire_ = false;
	isWalk_ = false;
	isInAir_ = false;

	//구르기 모션 가져오기
	static ConstructorHelpers::FObjectFinder<UAnimMontage> JUMP_MONTAGE(TEXT("/Game/My/Blueprints/Anim/Character/DiveJump_MT.DiveJump_MT"));

	//Fire Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> FIRE_MONTAGE(TEXT("/Game/My/Blueprints/Anim/Character/Fire_MT.Fire_MT"));

	//RestMontage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> REST_MONTAGE(TEXT("/Game/My/Blueprints/Anim/Character/BlendPose/Rest_IDLE_MT.Rest_IDLE_MT"));

	//Test
	static ConstructorHelpers::FObjectFinder<UAnimMontage> WALK_MONTAGE(TEXT("/Game/My/Blueprints/Anim/Character/BlendPose/Walk_BLEND_MT.Walk_BLEND_MT"));

	if (JUMP_MONTAGE.Succeeded())
	{
		diveMontage_ = JUMP_MONTAGE.Object;
	}

	if (FIRE_MONTAGE.Succeeded())
	{
		fireMontage_ = FIRE_MONTAGE.Object;
	}

	if (REST_MONTAGE.Succeeded())
	{
		restMontage_ = REST_MONTAGE.Object;
	}

	if (WALK_MONTAGE.Succeeded())
	{
		walkMontage_ = WALK_MONTAGE.Object;
	}
}

//Pawn Speed 사용
void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	Character_ = Cast<APlayerCharacter>(Pawn);

	if (::IsValid(Pawn))
	{
		if (Character_)
		{
			isFire_ = Character_->GetIsFire();
			isSprint_ = Character_->GetSprintBtn();
			isInAir_ = Character_->GetMovementComponent()->IsFalling();
		}

		currentChrSpeed_ = Pawn->GetVelocity().Size();

		//달리는 모션
		if (isSprint_)
		{
			isWalk_ = false;
			ChanageWeaponSocket(SPRINT_GRIPSOCKET);
		}

		//걷는 모션
		if (isWalk_)
		{
			ChanageWeaponSocket(FIRE_GRIPSOCKET);
		}

		//서있는 모션
		if (isRest_)
		{
			isWalk_ = false;
			ChanageWeaponSocket(FIRE_GRIPSOCKET);
		}

		//발사 모션
		if (isFire_)
		{
			ChanageWeaponSocket(FIRE_GRIPSOCKET);
		}
	}
	//ABLOG(Warning, TEXT("Walk Speed : %f"), currentChrSpeed_);
}

//DiveJump Montage
void UPlayerAnimInstance::PlayDiveJumpMontage()
{
	
}

//Fire Gun Montage
void UPlayerAnimInstance::PlayFireGunMontage()
{

}

void UPlayerAnimInstance::ChanageWeaponSocket(FName _name)
{
	FName WeaponSocket(_name);
	AGunWeapon* Weapon = Cast<AGunWeapon>(Character_->GetCurrentWeapon());

	if (Weapon != nullptr)
	{
		Weapon->AttachToComponent(Character_->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		Character_->SetWeaponLoc(Character_->GetMesh()->GetSocketLocation(WeaponSocket));
	}
}

//Tesst Montage
void UPlayerAnimInstance::PlayTestMontage()
{

}