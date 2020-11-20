// Fill out your copyright notice in the Description page of Project Settings.


#include "WarPlayerController.h"
#include "PlayerAnimInstance.h"

AWarPlayerController::AWarPlayerController()
{
	zoomInBtn_ = false;
}

void AWarPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AWarPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AWarPlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	bool zoomInBtn_Old = zoomInBtn_;

	Super::ProcessPlayerInput(DeltaTime, bGamePaused);

	if (myCharacter_ != nullptr)
	{
		if (zoomInBtn_Old && (zoomInBtn_Old == zoomInBtn_))
		{
			myCharacter_->SetViewMode(ViewMode::ZOOMIN);
		}
		else
		{
			myCharacter_->SetViewMode(ViewMode::COMMONVIEW);
		}
	}
}

void AWarPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("ZoomIn"), EInputEvent::IE_Pressed, this, &AWarPlayerController::ZoomInStarted);
	InputComponent->BindAction(TEXT("ZoomIn"), EInputEvent::IE_Released, this, &AWarPlayerController::ZoomInReleased);

	InputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &AWarPlayerController::ViewChange);

	InputComponent->BindAction(TEXT("DiveJump"), EInputEvent::IE_Pressed, this, &AWarPlayerController::DiveJump);

	InputComponent->BindAction(TEXT("RunSprint"), EInputEvent::IE_Pressed, this, &AWarPlayerController::RunSprintStart);
	InputComponent->BindAction(TEXT("RunSprint"), EInputEvent::IE_Released, this, &AWarPlayerController::RunSprintReleased);
}

void AWarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	myCharacter_ = Cast<APlayerCharacter>(GetCharacter());
}

void AWarPlayerController::ViewChange()
{
	currentView_ = myCharacter_->GetCurrentViewMode();
	switch (currentView_)
	{
	case ViewMode::TESTVIEW:
		//SetControlRotation(GetCharacter()->GetCharGetActorRotation());
		myCharacter_->SetViewMode(ViewMode::COMMONVIEW);
		break;

	case ViewMode::COMMONVIEW:
		//GetController()->SetControlRotation(springArm_->GetRelativeRotation());
		myCharacter_->SetViewMode(ViewMode::TESTVIEW);
		break;
	default:
		break;
	}
}

void AWarPlayerController::ZoomInStarted()
{
	zoomInBtn_ = true;
	ABLOG(Warning, TEXT("Let's Zoom in"));
}

void AWarPlayerController::ZoomInReleased()
{
	zoomInBtn_ = false;
}

//구르기 모션
void AWarPlayerController::DiveJump()
{
	auto AnimInstance = Cast<UPlayerAnimInstance>(GetCharacter()->GetMesh()->GetAnimInstance());

	if (AnimInstance != nullptr)
	{
		AnimInstance->PlayDiveJumpMontage();
	}

	if (myCharacter_ != nullptr)
	{
		ABLOG(Warning, TEXT("It's Dive Jump!!! %f"), myCharacter_->GetActorLocation().X);
	}
}

//뛰기 모션
void AWarPlayerController::RunSprintStart()
{
	sprintBtn_ = true;
	GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = SPRINT_SPEED;

	if (myCharacter_ != nullptr)
	{
		ABLOG(Warning, TEXT("It's Run Sprint Start!!! %f"), myCharacter_->GetActorLocation().X);
	}
}

void AWarPlayerController::RunSprintReleased()
{
	sprintBtn_ = false;
	GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;

	if (myCharacter_ != nullptr)
	{
		ABLOG(Warning, TEXT("It's Run Sprint Released!!! %f"), myCharacter_->GetActorLocation().X);
	}
}