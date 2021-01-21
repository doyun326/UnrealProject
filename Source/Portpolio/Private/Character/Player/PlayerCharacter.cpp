// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Player/PlayerCharacter.h"
#include "../Public/Character/Player/PlayerAnimInstance.h"
#include "../Public/Character/Player/WarPlayerController.h"
#include "../Public/Character/Player/PlayerStatComponent.h"
#include "../Public/Weapon/GunWeapon.h"
#include "../Public/Character/Player/WarPlayerState.h"
#include "..//Public/UI/PlayerHudWidget.h"

#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

#define ZOOMIN_FIELDVIEW	70.0f
#define COMMON_FIELDVIEW	90.0f
#define ZOOMIN_ARMLENGTH	100.0f
#define COMMON_ARMLENGTH	200.0f
#define CHANGEVIEW_SPEED	7.0f		//카메라봉 변환 속도

//Test 탄알 발사시 탄알 발사한 방향으로 회전
#define SHOOTTURN_SPEED		20.0f

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Character Mesh 설정
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> War_Alien(TEXT("/Game/My/Asset/Character/Player/ODGreen/Meshes/Wraith_ODGreen.Wraith_ODGreen"));

	if (War_Alien.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : War_Alien"));
		GetMesh()->SetSkeletalMesh(War_Alien.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));
	}
	
	//Animation 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> Alien_Anim(TEXT("/Game/My/Blueprints/Anim/Character/AlienAnim_BP.AlienAnim_BP_C"));

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

	//캐릭터 이동속도
	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;

	//PlayerStat 설정
	playerStat_ = CreateDefaultSubobject<UPlayerStatComponent>(TEXT("PLAYERSTAT"));

	if (playerStat_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : PlayerStat"));
	}

	isFire_ = false;
	isSprint_ = false;
	isZoomIn_ = false;

	SetViewMode(ViewMode::COMMONVIEW);
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

	playerController_->GetHudWidget()->BindPlayerStat(playerStat_);
	playerStat_->SetNewLevel(warPlayerState_->GetCharacterLevel());

	//playerAnim_->OnChangeWalkSocket.BindUFunction(this, FName("WalkSocket"));
	//playerAnim_->OnChangeRestSocket.BindUFunction(this, FName("WalkSocket"));
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, GetWorld()->GetName());
}

// Called every frame
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
	//DrawDebugLine(GetWorld(), startPoint_, endPoint_, FColor::Red, false, 0.5, 0, 1);
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

	/////////////////////////////////////Test/////////////////////////////////////
	FVector charStart = GetActorLocation();
	FVector charForwardVector = GetActorForwardVector();

	FHitResult chrhit;
	FVector charEnd = charStart + charForwardVector * 5000.0f;
	charStart = charStart + (charForwardVector * 100.0f);
	FCollisionQueryParams CharParams;
	CharParams.AddIgnoredActor(this);

	/*Draw rayCast debug Line START*/
	//DrawDebugLine(GetWorld(), charStart, charEnd, FColor::Blue, false, 0.5, 0, 1);
	/*Draw rayCast debug Line START*/
	/////////////////////////////////////Test/////////////////////////////////////
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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
	//weapon_->OnFire(isFire_);
	weapon_->ShootBullet();
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

USkeletalMeshComponent* APlayerCharacter::GetSkelMesh()
{
	return GetMesh();
}

bool APlayerCharacter::GetIsWalking()
{
	return isWalk_;
}

bool	APlayerCharacter::GetIsZoom()
{
	return isZoomIn_;
}