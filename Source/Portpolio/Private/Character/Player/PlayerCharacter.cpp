// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Player/PlayerCharacter.h"
#include "../Public/Character/Player/PlayerAnimInstance.h"
#include "../Public/Character/Player/WarPlayerController.h"
#include "../public/Weapon/GunWeapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

#define ZOOMIN_FIELDVIEW 70.0f
#define COMMON_FIELDVIEW 90.0f
#define ZOOMIN_ARMLENGTH 100.0f
#define COMMON_ARMLENGTH 200.0f
#define CHANGEVIEW_SPEED 7.0f		//카메라봉 변환 속도
#define SHOOTTURN_SPEED 20.0f

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Character Mesh 설정
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> War_Alien(TEXT("/Game/My/Asset/Character/Player/Alien.Alien"));

	if (War_Alien.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(War_Alien.Object);
	}

	//Mesh위치 설정
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));

	//Animation 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> Alien_Anim(TEXT("/Game/My/Blueprints/Anim/Character/Alien_BP.Alien_BP_C"));

	if (Alien_Anim.Succeeded())
	{
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

	isFire_ = false;
	isSprint_ = false;

	/*Test View*/
	armRotationTo_ = FRotator::ZeroRotator;
	armRotationSpeed_ = 10.0f;
	directionToMove_ = FVector::ZeroVector;


	SetViewMode(ViewMode::COMMONVIEW);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	playerController_ = Cast<AWarPlayerController>(GetController());

	//Defalut weapon 장착
	FName WeaponSocket(TEXT("RestGripPoint"));
	weapon_ = GetWorld()->SpawnActor<AGunWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);

	if (weapon_ != nullptr)
	{
		weapon_->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		socketLocation_ = GetMesh()->GetSocketLocation(WeaponSocket);

	}

	playerAnim_ = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	if (playerAnim_ != nullptr)
	{
		//playerAnim_->OnChangeWalkSocket.BindUFunction(this, FName("WalkSocket"));
		//playerAnim_->OnChangeRestSocket.BindUFunction(this, FName("WalkSocket"));
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//시점 변환 보간 작업
	cameraArm_->TargetArmLength = FMath::FInterpTo(cameraArm_->TargetArmLength, armLengthTo_, DeltaTime, CHANGEVIEW_SPEED);

	//Location, Rotation 저장
	PlayerLocation_ = GetActorLocation();
	PlayerRotator_ = GetActorRotation();

	if (isFire_)
	{
		if (weapon_ != nullptr)
		{
			FRotator NewRot = FMath::RInterpTo(PlayerRotator_, weapon_->GetShootRot(), DeltaTime, SHOOTTURN_SPEED);
			//SetActorRotation(NewRot);
			lookPitch_ = FMath::Clamp(NewRot.Pitch, -90.0f, 90.0f);
			//ABLOG(Warning, TEXT("Roll : %f		Pitch : %f		Yaw : %f"), NewRot.Roll, NewRot.Pitch, NewRot.Yaw);
		}
	}
	
	//테스트 확인용
	//ABLOG(Warning, TEXT("%f		%f		%f"), weapon_->GetShootRot().Pitch, weapon_->GetShootRot().Roll, weapon_->GetShootRot().Yaw);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
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
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

		break;
	}
	
	case ViewMode::ZOOMIN:
	{
		GetCharacterMovement()->MaxWalkSpeed = 800.0f;
		armLengthTo_ = ZOOMIN_ARMLENGTH;
		camera_->FieldOfView = ZOOMIN_FIELDVIEW;
		break;
	}
	}
}

//raycast를 이용한 탄환 발사
void APlayerCharacter::OnFireSwitch(bool _firBtn)
{
	isFire_ = _firBtn;
	weapon_->SetPlayerCamInfo(camera_->GetComponentLocation(), camera_->GetForwardVector(), PlayerLocation_, cameraArm_->TargetArmLength);
	weapon_->OnFire(_firBtn);
}

void APlayerCharacter::PlayMontageDiveJump()
{
	auto AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInstance != nullptr)
	{
		AnimInstance->PlayDiveJumpMontage();
	}
}

AGunWeapon* APlayerCharacter::GetCurrentWeapon()
{
	return weapon_;
}

void APlayerCharacter::SetWeaponLoc(FVector _newLoc)
{
	socketLocation_ = _newLoc;
}

ControlMode APlayerCharacter::GetCurrentControllMode()
{
	return currentControlMode_;
}

FVector APlayerCharacter::GetPlayerLocation()
{
	return PlayerLocation_;
}

FRotator APlayerCharacter::GetPlayerRotator()
{
	return PlayerRotator_;
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

float APlayerCharacter::GetLookClampPitch()
{
	return lookPitch_;
}

USkeletalMeshComponent* APlayerCharacter::GetSkelMesh()
{
	return GetMesh();
}