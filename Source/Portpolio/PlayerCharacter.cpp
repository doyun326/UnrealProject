// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Character Mesh 설정
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> War_Alien(TEXT("/Game/My/Asset/Character/Player/AlienSoldier.AlienSoldier"));

	if (War_Alien.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(War_Alien.Object);
		ABLOG(Warning, TEXT("Complate!"))
	}

	//Mesh위치 설정
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	//Animation 설정
	static ConstructorHelpers::FClassFinder<UAnimInstance> Alien_Anim(TEXT("/Game/My/Blueprints/Anim/Character/Player/AlienAnim_BP.AlienAnim_BP_C"));

	if (Alien_Anim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(Alien_Anim.Class);
	}

	//카메라 설정
	cameraArm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("CAMERAARM"));
	camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	cameraArm_->SetupAttachment(GetCapsuleComponent());
	camera_->SetupAttachment(cameraArm_);
	cameraArm_->TargetArmLength = 400.0f;
	cameraArm_->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	armLengthTo_ = 0.0f;

	SetViewMode(ViewMode::COMMONVIEW);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	case ViewMode::COMMONVIEW:
	{
		cameraArm_->TargetArmLength = 200.0f;
		camera_->SetRelativeLocationAndRotation(FVector(0.0f, 100.0f, 80.0f), FRotator(-3.0f, 0.0f, 0.0f));

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
	
	case ViewMode::FREEVIEW:
	{

		break;
	}
	default:
	{
		break;
	}
	}
}

ControlMode APlayerCharacter::GetCurrentControllMode()
{
	return currentControlMode_;
}

ViewMode APlayerCharacter::GetCurrentViewMode()
{
	return ViewMode();
}
