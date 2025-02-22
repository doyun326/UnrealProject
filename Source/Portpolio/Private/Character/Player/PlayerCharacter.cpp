// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Player/PlayerCharacter.h"
#include "../Public/Character/Player/PlayerAnimInstance.h"
#include "../Public/Character/Player/WarPlayerController.h"
#include "../Public/Character/Player/PlayerStatComponent.h"
#include "../Public/Weapon/GunWeapon.h"
#include "../Public/Character/Player/WarPlayerState.h"
#include "../Public/UI/PlayerHudWidget.h"
#include "../Public/Object/BaseInteractable.h"
#include "../Public/GameSetting/WarGameInstance.h"

#include "NiagaraSystem.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

#define PLAYERMESH_PATH			"/Game/My/Asset/Character/Player/ODGreen/Meshes/Wraith_ODGreen.Wraith_ODGreen"
#define PLAYERANIM_PATH			"/Game/My/Blueprints/Anim/Character/AlienAnim_BP.AlienAnim_BP_C"
#define FLASHEFFECT_PATH		"/Game/My/Asset/Niagara/Flash/FlashSystem.FlashSystem"
#define LIMITCLEAR_PATH			"/Game/My/Asset/Niagara/Flash/LimitClearSystem.LimitClearSystem"
#define CAMERASHAKECLASS_PATH	"/Script/Portpolio.MyCameraShake"


#define ZOOMIN_FIELDVIEW	70.0f
#define COMMON_FIELDVIEW	90.0f
#define ZOOMIN_ARMLENGTH	100.0f
#define COMMON_ARMLENGTH	200.0f
#define CHANGEVIEW_SPEED	7.0f		//카메라봉 변환 속도
#define SHOOTTURN_SPEED		20.0f		//Test 탄알 발사시 탄알 발사한 방향으로 회전
#define EFFECTPLAY_COUNT	3

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Character Mesh 설정
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> War_Alien(TEXT(PLAYERMESH_PATH));

	if (War_Alien.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : War_Alien"));
		GetMesh()->SetSkeletalMesh(War_Alien.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));
	}
	
	//Animation 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> Alien_Anim(TEXT(PLAYERANIM_PATH));

	if (Alien_Anim.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : Alien_Anim"));
		GetMesh()->SetAnimInstanceClass(Alien_Anim.Class);
	}

	//카메라 설정
	cameraArm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("CAMERAARM"));
	camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	cameraArm_->SetupAttachment(GetCapsuleComponent());
	camera_->SetupAttachment(cameraArm_);
	cameraArm_->TargetArmLength = 200.0f;
	cameraArm_->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	armLengthTo_ = 0.0f;	//카메라봉 길이

	//ShakeCamera Setting
	static ConstructorHelpers::FClassFinder<UCameraShake> CAMERA_SHAKE(TEXT(CAMERASHAKECLASS_PATH));

	if (CAMERA_SHAKE.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : CAMERA_SHAKE"));
		myShake_ = (UClass*)CAMERA_SHAKE.Class;
	}

	//PlayerStat 설정
	playerStat_ = CreateDefaultSubobject<UPlayerStatComponent>(TEXT("PLAYERSTAT"));

	if (playerStat_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : PlayerStat"));
		return;
	}

	//Collision Preset Setting
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	//Flahs System
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FLASH_EFFECT(TEXT(FLASHEFFECT_PATH));

	if (FLASH_EFFECT.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : FLASH_EFFECT"));
		flashEffect_ = FLASH_EFFECT.Object;
	}

	//Flahs System
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> LIMIT_EFFECT(TEXT(LIMITCLEAR_PATH));

	if (LIMIT_EFFECT.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : LIMIT_EFFECT"));
		limitEffect_ = LIMIT_EFFECT.Object;
	}
	
	//Actor 기초 세팅
	SetActorHiddenInGame(true);
	SetCanBeDamaged(false);

	isFire_ = false;
	isSprint_ = false;
	isZoomIn_ = false;
	isInteract_ = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	playerController_ = Cast<AWarPlayerController>(GetController());
	warPlayerState_ = Cast<AWarPlayerState>(GetPlayerState());

	//Defalut weapon 장착
	FName WeaponSocket(TEXT("RestGripPoint"));
	weapon_ = GetWorld()->SpawnActor<AGunWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);

	if (playerController_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : playerController_"));
		return;
	}

	if (weapon_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : weapon_"));
		return;
	}

	MuzzleSocket = "Muzzle_01";
	weapon_->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	weapon_->SetMuzzleSocketPosition(GetMesh()->GetSocketLocation(MuzzleSocket), GetMesh()->GetSocketRotation(MuzzleSocket));

	//Loading
	if (warPlayerState_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : warPlayerState_"));
		return;
	}

	warInstance_ = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (warInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarInstnace"));
		return;
	}

	warInstance_->onFlashEffect.AddUObject(this, &APlayerCharacter::PlayFlashEffect);
	warInstance_->onLimitEffect.AddUObject(this, &APlayerCharacter::PlayLimintClearEffect);

	SetCharacterState(ECharacterState::READY);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//시점 변환 보간 작업
	cameraArm_->TargetArmLength = FMath::FInterpTo(cameraArm_->TargetArmLength, armLengthTo_, DeltaTime, CHANGEVIEW_SPEED);

	//Location, Rotation 저장
	playerLocation_ = this->GetActorLocation();
	playerRotator_ = this->GetActorRotation();

	if (weapon_ != nullptr)
	{
		weapon_->SetMuzzleSocketPosition(GetMesh()->GetSocketLocation(MuzzleSocket), GetMesh()->GetSocketRotation(MuzzleSocket));
	}
	else
	{
		ABLOG(Error, TEXT("Nullptr : weapon"));
	}

	startPoint_ = camera_->GetComponentLocation();
	camArmLength_ = cameraArm_->TargetArmLength;
	forwardVector_ = camera_->GetForwardVector();

	//RayCast
	FHitResult Outhit;

	endPoint_ = startPoint_ + (forwardVector_ * 5000.0f);
	startPoint_ = startPoint_ + (forwardVector_ * camArmLength_);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this->GetOwner());

	bool RayHit = GetWorld()->LineTraceSingleByChannel(Outhit, startPoint_, endPoint_, ECC_Visibility, CollisionParams);

	/*Draw rayCast debug Line START*/
#ifdef DRAW_DEBUGHELPER
	{
		//DrawDebugLine(GetWorld(), startPoint_, endPoint_, FColor::Red, false, 0.5, 0, 1);
	}
#endif
	/*Draw rayCast debug Line END*/

	//공격, 줌인시 캐릭터 회전
	if (isFire_ || currentViewMode_ == ViewMode::ZOOMIN)
	{
		FRotator TargetRoatator = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), endPoint_);
		playerRotator_ = FMath::RInterpTo(playerRotator_, TargetRoatator, DeltaTime, 20.0f);

		fireLookPosition_ = endPoint_;

		if (RayHit)
		{
			FVector RayEndVec = Outhit.Location;

			TargetRoatator = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), RayEndVec);
			playerRotator_ = FMath::RInterpTo(playerRotator_, TargetRoatator, DeltaTime, 20.0f);

			fireLookPosition_ = RayEndVec;
		}

		lookPitch_ = playerRotator_.Pitch;
		playerRotator_.Pitch = 0.0f;
		SetActorRotation(playerRotator_);	//Set PlayerLookRotator
		weapon_->SetAimVector(fireLookPosition_);	//Set PlayerAimVector
	}
	isInteract();
	
	/*Draw rayCast debug Line START*/
#ifdef DRAW_DEBUGHELPER
	{
		/*FVector charStart = GetActorLocation();
		FVector charForwardVector = GetActorForwardVector();

		FHitResult chrhit;
		FVector charEnd = charStart + charForwardVector * 5000.0f;
		charStart = charStart + (charForwardVector * 100.0f);
		FCollisionQueryParams CharParams;
		CharParams.AddIgnoredActor(this);

		DrawDebugLine(GetWorld(), charStart, charEnd, FColor::Blue, false, 0.5, 0, 1);*/
	}
#endif //DRAW_DEBUGHELPER
	/*Draw rayCast debug Line START*/

	if (warInstance_->GetPlayingSequence())
	{
		playerController_->HideHUD();
	}
	else
	{
		playerController_->ShowHUD();
	}
	
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//BindAction
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &APlayerCharacter::Interact);
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	playerAnim_ = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	if (playerAnim_ != nullptr)
	{
		ABLOG(Warning, TEXT("Success : PlayerAnim"));
		playerAnim_->onFireBulletCheck_.AddUObject(this, &APlayerCharacter::WeaponFire);
	}
}

void APlayerCharacter::SetViewMode(ViewMode _newMode)
{
	currentViewMode_ = _newMode;

	switch (currentViewMode_)
	{
	case ViewMode::COMMONVIEW:
	{
		camera_->FieldOfView = COMMON_FIELDVIEW;
		armLengthTo_ = COMMON_ARMLENGTH;
		camera_->SetRelativeLocationAndRotation(FVector(0.0f, 80.0f, 80.0f), FRotator(-3.0f, 0.0f, 0.0f));

		cameraArm_->bUsePawnControlRotation = true;
		cameraArm_->bInheritPitch = true;
		cameraArm_->bInheritRoll = true;
		cameraArm_->bInheritYaw = true;
		cameraArm_->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;

		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
		isZoomIn_ = false;
		break;
	}
	
	case ViewMode::ZOOMIN:
	{
		GetCharacterMovement()->MaxWalkSpeed = 800.0f;
		armLengthTo_ = ZOOMIN_ARMLENGTH;
		camera_->FieldOfView = ZOOMIN_FIELDVIEW;
		isZoomIn_ = true;
		break;
	}
	}
}

void APlayerCharacter::OnFire(bool _firBtn)
{
	isFire_ = _firBtn;
}

void APlayerCharacter::WeaponFire()
{
	if (weapon_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : weapon"));
		return;
	}

	ABLOG(Error, TEXT("Damage : %d"), playerStat_->GetDamageRatio());
	weapon_->SetPlayerDamage(playerStat_->GetDamageRatio());
	weapon_->ShootBullet();

	if (playerController_ == nullptr || myShake_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : myShake"));
		return;
	}
	playerController_->PlayerCameraManager->PlayCameraShake(myShake_, 0.008f);
}

void APlayerCharacter::isInteract()
{
	FHitResult OutHit;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, startPoint_, endPoint_, ECC_Visibility))
	{
		ABaseInteractable* Object = Cast<ABaseInteractable>(OutHit.Actor);

		if (Object)
		{
			isInteract_ = true;
		}
		else
		{	
			isInteract_ = false;
		}
		warPlayerState_->ChangeInteractText(isInteract_);
	}
}

//Object Interact
void APlayerCharacter::Interact()
{
	FHitResult OutHit;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, startPoint_, endPoint_, ECC_Visibility))
	{
		ABaseInteractable* Object = Cast<ABaseInteractable>(OutHit.Actor);

		if (Object)
		{
			Object->Interact();
		}
	}
}

void APlayerCharacter::SetCharacterState(ECharacterState _newState)
{
	currentState_ = _newState;

	if (playerStat_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : PlayerStatComponent"));
		return;
	}

	if (playerController_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : PlayerController"));
		return;
	}
	
	switch (currentState_)
	{
	case ECharacterState::LOADING:
	{
		SetActorHiddenInGame(true);
		SetCanBeDamaged(false);
		DisableInput(playerController_);
		break;
	}

	case ECharacterState::READY:
	{
		SetActorHiddenInGame(false);
		SetCanBeDamaged(true);

		playerController_->GetHudWidget()->BindPlayerStat(playerStat_);
		playerStat_->SetNewLevel(warPlayerState_->GetCharacterLevel());

		playerStat_->onHpIsZero_.AddLambda([this]()->void 
			{
				SetCharacterState(ECharacterState::DEAD);
			});

		SetViewMode(ViewMode::COMMONVIEW);
		GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
		EnableInput(playerController_);
		break;
	}

	case ECharacterState::DEAD:
	{
		GetMesh()->SetHiddenInGame(false);
		SetActorEnableCollision(false);
		SetCanBeDamaged(false);
		DisableInput(playerController_);
		break;
	}
	}
}

void APlayerCharacter::PlayFlashEffect()
{
	FName NoneName("none");
	for(int32 i = 0; i < EFFECTPLAY_COUNT; i++)
	{
		UNiagaraComponent* effect = UNiagaraFunctionLibrary::SpawnSystemAttached(flashEffect_, GetMesh(), NoneName, GetMesh()->GetRelativeLocation(), GetMesh()->GetRelativeRotation(), FVector(1.0f, 1.0f, 1.0f), EAttachLocation::KeepRelativeOffset, false, ENCPoolMethod::None);
	}
}
	

void APlayerCharacter::PlayLimintClearEffect()
{
	FName NoneName("none");
	for (int32 i = 0; i < EFFECTPLAY_COUNT; i++)
	{
		UNiagaraComponent* effect = UNiagaraFunctionLibrary::SpawnSystemAttached(limitEffect_, GetMesh(), NoneName, GetMesh()->GetRelativeLocation(), GetMesh()->GetRelativeRotation(), FVector(1.0f, 1.0f, 1.0f), EAttachLocation::KeepRelativeOffset, false, ENCPoolMethod::None);
	}
	LimitLevelUp();
}

void APlayerCharacter::InfinityMode()
{

}

void APlayerCharacter::LimitLevelUp()
{
	playerStat_->SetNewLevel(warPlayerState_->GetLimitLevel());
}

ECharacterState	APlayerCharacter::GetCharacterState() const
{
	return currentState_;
}

ControlMode APlayerCharacter::GetCurrentControllMode()
{
	return currentControlMode_;
}

FVector APlayerCharacter::GetPlayerLocation()
{
	return playerLocation_;
}

FRotator APlayerCharacter::GetPlayerRotator()
{
	return playerRotator_;
}

bool APlayerCharacter::GetIsFire()
{
	return isFire_;
}

bool APlayerCharacter::GetSprintBtn()
{
	return isSprint_;
}

void APlayerCharacter::SetSprintBtn(bool _newState)
{
	isSprint_ = _newState;
}

float APlayerCharacter::GetLookPitch()
{
	return lookPitch_;
}

bool APlayerCharacter::GetIsWalking()
{
	return isWalk_;
}

bool APlayerCharacter::GetIsZoom()
{
	return isZoomIn_;
}