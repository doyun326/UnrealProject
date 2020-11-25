// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "WarWeapon.h"
#include "DrawDebugHelpers.h"
#include "PlayerAnimInstance.h"
#include "WarPlayerController.h"
#include "Components/SkeletalMeshComponent.h"

#define ZOOMIN_FIELDVIEW 70.0f
#define COMMON_FIELDVIEW 90.0f
#define ZOOMIN_ARMLENGTH 100.0f
#define COMMON_ARMLENGTH 200.0f
#define CHANGEVIEW_SPEED 7.0f		//ī�޶�� ��ȯ �ӵ�

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Character Mesh ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> War_Alien(TEXT("/Game/My/Asset/Character/Player/Alien.Alien"));

	if (War_Alien.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(War_Alien.Object);
		ABLOG(Warning, TEXT("Complate!"))
	}

	//Mesh��ġ ����
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));

	//Animation ����
	static ConstructorHelpers::FClassFinder<UAnimInstance> Alien_Anim(TEXT("/Game/My/Blueprints/Anim/Character/Alien_BP.Alien_BP_C"));

	if (Alien_Anim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(Alien_Anim.Class);
	}

	//ī�޶� ����
	cameraArm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("CAMERAARM"));
	camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	cameraArm_->SetupAttachment(GetCapsuleComponent());
	camera_->SetupAttachment(cameraArm_);
	cameraArm_->TargetArmLength = 200.0f;
	cameraArm_->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	armLengthTo_ = 0.0f;	//ī�޶�� ����

	//ĳ���� �̵��ӵ�
	GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;

	//���� ����
	isShooting_ = false;

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

	//Defalut weapon ����
	FName WeaponSocket(TEXT("RestGripPoint"));
	weapon_ = GetWorld()->SpawnActor<AWarWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);

	if (weapon_ != nullptr)
	{
		weapon_->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		socketLocation_ = GetMesh()->GetSocketLocation(WeaponSocket);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//���� ��ȯ ���� �۾�
	cameraArm_->TargetArmLength = FMath::FInterpTo(cameraArm_->TargetArmLength, armLengthTo_, DeltaTime, CHANGEVIEW_SPEED);

	switch (currentViewMode_)
	{
	case ViewMode::COMMONVIEW:
		break;

	case ViewMode::TESTVIEW:
		cameraArm_->GetRelativeRotation() = FMath::RInterpTo(cameraArm_->GetRelativeRotation(), armRotationTo_, DeltaTime, armRotationSpeed_);

		if (directionToMove_.SizeSquared() > 0.0f)
		{
			//FRoationMatrix�� ȸ���� ��ǥ�踦 �����ϴ� ���
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(directionToMove_).Rotator());
			AddMovementInput(directionToMove_);
		}
		break;
	default:
		break;
	}

	ChangeGripSocket();
	ABLOG(Warning, TEXT("is walk : %d"), isWalk_);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::SetControllMode(ControlMode _newMode)
{
	currentControlMode_ = _newMode;

	switch (currentControlMode_)
	{
		case ControlMode::PLAYER:
		{
		}
	
	default:
		break;
	}
}

void APlayerCharacter::SetViewMode(ViewMode _newMode)
{
	currentViewMode_ = _newMode;

	switch (currentViewMode_)
	{
	case ViewMode::TESTVIEW:
	{
		armLengthTo_ = 800.0f;

		cameraArm_->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

		cameraArm_->bUsePawnControlRotation = false;
		cameraArm_->bInheritPitch = false;
		cameraArm_->bInheritRoll = false;
		cameraArm_->bInheritYaw = false;
		cameraArm_->bDoCollisionTest = false;
		bUseControllerRotationYaw = true;

		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}

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
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
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

//raycast�� �̿��� źȯ �߻�
void APlayerCharacter::OnFireSwitch(bool _firBtn)
{
	FHitResult OutHit;
	FVector StartPoint = camera_->GetComponentLocation();
	FVector ForwardVector = camera_->GetForwardVector();
	FVector EndPoint = StartPoint + (ForwardVector * 5000.0f);
	FCollisionQueryParams CollisionParams;

	StartPoint = StartPoint + (ForwardVector * cameraArm_->TargetArmLength);
	CollisionParams.AddIgnoredActor(this->GetOwner());

	rayHit_ = GetWorld()->LineTraceSingleByChannel(OutHit, StartPoint, EndPoint, ECC_Visibility, CollisionParams);

	if (_firBtn)
	{
		if (!isShooting_)
		{
			isShooting_ = true;
			GetWorld()->GetTimerManager().SetTimer(shotDelayTimerHandle_, this, &APlayerCharacter::OnFire, 0.3f, true);
		}
	}
	else
	{
		if (isShooting_)
		{
			isShooting_ = false;
			GetWorld()->GetTimerManager().ClearTimer(shotDelayTimerHandle_);
		}	
	}

	/*Draw rayCast debug Line START*/
	//DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Green, false, 1, 0, 1);
	/*Draw rayCast debug Line END*/
}

void APlayerCharacter::OnFire()
{
	if (rayHit_)
	{
		ABLOG(Warning, TEXT("shot and Actor Hit"));
	}
	else
	{
		ABLOG(Warning, TEXT("shot and Actor Not Hit"));
	}
}

void APlayerCharacter::PlayMontageDiveJump()
{
	auto AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInstance != nullptr)
	{
		AnimInstance->PlayDiveJumpMontage();
	}
}

void APlayerCharacter::ChangeGripSocket()
{
	FName WeaponSocket;

	if (isWalk_) //�ȱ� �� ���
	{
		if (playerController_->GetFireBtn())
		{
			WeaponSocket = FIRE_GRIPSOCKET;
		}
		else
		{
			WeaponSocket = WALK_GRIPSOCKET;
		}
	}
	else		 //�ȴ� ���� �ƴҶ�
	{
		if (playerController_->GetFireBtn())
		{
			WeaponSocket = FIRE_GRIPSOCKET;
			socketLocation_ = GetMesh()->GetSocketLocation(WeaponSocket);
		}
		else
		{
			WeaponSocket = REST_GRIPSOCKET;
		}
	}
	//WeaponSocket = REST_GRIPSOCKET;

	if (weapon_ != nullptr)
	{
		weapon_->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		socketLocation_ = GetMesh()->GetSocketLocation(WeaponSocket);
	}
}

ControlMode APlayerCharacter::GetCurrentControllMode()
{
	return currentControlMode_;
}

ViewMode APlayerCharacter::GetCurrentViewMode()
{
	return currentViewMode_;
}

bool APlayerCharacter::GetIsShooting()
{
	return isShooting_;
}