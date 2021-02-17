// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Player/PlayerAnimInstance.h"
#include "../Public/Character/Player/WarPlayerController.h"
#include "../public/Weapon/GunWeapon.h"

#include "Niagara/Public/NiagaraFunctionLibrary.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{	
	//RestMontage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> REST_MONTAGE(TEXT("/Game/My/Blueprints/Anim/Character/BlendPose/Rest_IDLE_MT.Rest_IDLE_MT"));

	//Attack Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> FIRE_MONTAGE(TEXT("/Game/My/Blueprints/Anim/Character/Fire_MT.Fire_MT"));

	if (FIRE_MONTAGE.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : FIRE_MONTAGE"));
		attackMT_ = FIRE_MONTAGE.Object;
	}

	if (REST_MONTAGE.Succeeded())
	{
		restMontage_ = REST_MONTAGE.Object;
	}

	currentChrSpeed_ = 0.0f;
	isFire_ = false;
	//isWalk_ = false;
	isInAir_ = false;
	isLoby_ = false;
	isZoom_ = false;
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
			isWalk_ = Character_->GetIsWalking();
			lookPitch_ = Character_->GetLookPitch();
			currentChrSpeed_ = Pawn->GetVelocity().Size();
			isZoom_ = Character_->GetIsZoom();
		}

		//달리는 모션
		if (isSprint_)
		{
			isWalk_ = false;
			isFire_ = false;
		}

		//걷는 모션
		if (isWalk_)
		{

		}

		//서있는 모션
		if (isRest_)
		{
			
		}

		//발사 모션
		if (isFire_)
		{
			
		}
	}
	//ABLOG(Warning, TEXT("Walking: %d"), isWalk_);
	//ABLOG(Warning, TEXT("Walk Speed : %f"), currentChrSpeed_);
	//ABLOG(Warning, TEXT("Walk Speed : %f"), lookPitch_);

	if (GetWorld()->GetName() == "SpaceShip_Loby")
	{
		isLoby_ = true;
	}
	else
	{
		isLoby_ = false;
	}
	//ABLOG(Warning, TEXT("%d"), isLoby_);
	//ABLOG(Warning, TEXT("%d"), isFire_);
}

void UPlayerAnimInstance::AnimNotify_FireBullet()
{
	onFireBulletCheck_.Broadcast();
}

//Fire Gun Montage
void UPlayerAnimInstance::PlayFireMontage()
{
	Montage_Play(attackMT_, 1.0f);
}