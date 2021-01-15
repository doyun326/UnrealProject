// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Player/PlayerAnimInstance.h"
#include "../Public/Character/Player/WarPlayerController.h"
#include "../public/Weapon/GunWeapon.h"

#include "Niagara/Public/NiagaraFunctionLibrary.h"

#define FLASH_EFFECT_PATH "/Game/My/Asset/Niagara/Flash/FlashSystem.FlashSystem"
#define FLASH_SYSTEM_PATH "/Game/My/Asset/Niagara/Flash/FlashSystem.FlashSystem"

UPlayerAnimInstance::UPlayerAnimInstance()
{	
	currentChrSpeed_ = 0.0f;
	isFire_ = false;
	//isWalk_ = false;
	isInAir_ = false;

	//구르기 모션 가져오기
	static ConstructorHelpers::FObjectFinder<UAnimMontage> JUMP_MONTAGE(TEXT("/Game/My/Blueprints/Anim/Character/DiveJump_MT.DiveJump_MT"));

	//RestMontage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> REST_MONTAGE(TEXT("/Game/My/Blueprints/Anim/Character/BlendPose/Rest_IDLE_MT.Rest_IDLE_MT"));

	//Test
	static ConstructorHelpers::FObjectFinder<UAnimMontage> WALK_MONTAGE(TEXT("/Game/My/Blueprints/Anim/Character/BlendPose/Walk_BLEND_MT.Walk_BLEND_MT"));

	//Flash Effect
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FLASH_EFFECT(TEXT(FLASH_EFFECT_PATH));

	//Flahs System
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FLASH_SYSTEM(TEXT(FLASH_SYSTEM_PATH));

	if (JUMP_MONTAGE.Succeeded())
	{
		diveMontage_ = JUMP_MONTAGE.Object;
	}

	if (REST_MONTAGE.Succeeded())
	{
		restMontage_ = REST_MONTAGE.Object;
	}

	if (WALK_MONTAGE.Succeeded())
	{
		walkMontage_ = WALK_MONTAGE.Object;
	}

	if (FLASH_EFFECT.Succeeded() && FLASH_SYSTEM.Succeeded())
	{
		flashEffect_ = FLASH_EFFECT.Object;
		flashSystem_ = FLASH_SYSTEM.Object;
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
			characterMesh_ = Character_->GetSkelMesh();
			isWalk_ = Character_->GetIsWalking();
			lookPitch_ = Character_->GetLookPitch();
		}

		currentChrSpeed_ = Pawn->GetVelocity().Size();

		//달리는 모션
		if (isSprint_)
		{
			isWalk_ = false;
			ChanageWeaponSocket(SPRINT_GRIPSOCKET);
			
			//NiagaraSystem C++코드화, 추후 적당한 위치로 옮겨놈
			//FName NoneName("none");
			//UNiagaraComponent* effect = UNiagaraFunctionLibrary::SpawnSystemAttached(flashSystem_, characterMesh_, test, characterMesh_->GetRelativeLocation(), characterMesh_->GetRelativeRotation(), FVector(1.0f, 1.0f, 1.0f), EAttachLocation::KeepRelativeOffset, false, ENCPoolMethod::None);
		}

		//걷는 모션
		if (isWalk_)
		{
			ChanageWeaponSocket(FIRE_GRIPSOCKET);
		}

		//서있는 모션
		if (isRest_)
		{
			ChanageWeaponSocket(FIRE_GRIPSOCKET);
		}

		//발사 모션
		if (isFire_)
		{
			//ABLOG(Warning, TEXT("Firing: %d"), isWalk_);
			ChanageWeaponSocket(FIRE_GRIPSOCKET);
		}
	}
	//ABLOG(Warning, TEXT("Walking: %d"), isWalk_);
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