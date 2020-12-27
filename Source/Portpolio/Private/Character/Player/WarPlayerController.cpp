// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Character/Player/WarPlayerController.h"
#include "../Public/Character/Player/PlayerAnimInstance.h"

#include "Engine/Engine.h"

AWarPlayerController::AWarPlayerController()
{
	zoomInBtn_ = false;
	sprintBtn_ = false;
	fireBtn_ = false;
	testBtn_ = false;
}

void AWarPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ABLOG(Warning, TEXT("Bind PlayerController"));
}

void AWarPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

}

void AWarPlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	bool zoomInBtn_old = zoomInBtn_;
	bool fireBtn_old = fireBtn_;
	bool sprintBtn_old = sprintBtn_;

	bool testBtn_old = testBtn_;

	Super::ProcessPlayerInput(DeltaTime, bGamePaused);

	if (myCharacter_ == nullptr)
	{
		return;
	}

	//Mouse Zoom In/out
	if (zoomInBtn_old && (zoomInBtn_old == zoomInBtn_))
	{
		myCharacter_->SetViewMode(ViewMode::ZOOMIN);
	}
	else
	{	
		myCharacter_->SetViewMode(ViewMode::COMMONVIEW);
	}

	//RayCast Hit and fire
	if (fireBtn_old && (fireBtn_old == fireBtn_))
	{
		myCharacter_->OnFireSwitch(true);
	}
	else
	{
		myCharacter_->OnFireSwitch(false);
	}

	//sprint
	if (sprintBtn_old && (sprintBtn_old == sprintBtn_))
	{
		myCharacter_->SetSprintBtn(true);
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = SPRINT_SPEED;
	}
	else
	{
		myCharacter_->SetSprintBtn(false);
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
	}

	//Test
	/*if (testBtn_old && (testBtn_old == testBtn_))
	{
		myCharacter_->PlayTestMotion(true);
	}
	else
	{
		myCharacter_->PlayTestMotion(false);
	}*/
}

void AWarPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("DiveJump"), EInputEvent::IE_Pressed, this, &AWarPlayerController::DiveJump);

	InputComponent->BindAction(TEXT("ZoomIn"), EInputEvent::IE_Pressed, this, &AWarPlayerController::ZoomInStarted);
	InputComponent->BindAction(TEXT("ZoomIn"), EInputEvent::IE_Released, this, &AWarPlayerController::ZoomInReleased);
	
	InputComponent->BindAction(TEXT("RunSprint"), EInputEvent::IE_Pressed, this, &AWarPlayerController::RunSprintStart);
	InputComponent->BindAction(TEXT("RunSprint"), EInputEvent::IE_Released, this, &AWarPlayerController::RunSprintReleased);

	InputComponent->BindAction(TEXT("OnFire"), EInputEvent::IE_Pressed, this, &AWarPlayerController::OnFireStart);
	InputComponent->BindAction(TEXT("OnFire"), EInputEvent::IE_Released, this, &AWarPlayerController::OnFireReleased);

	//Test
	InputComponent->BindAction(TEXT("walk"), EInputEvent::IE_Pressed, this, &AWarPlayerController::OnTestMotionStart);
	InputComponent->BindAction(TEXT("walk"), EInputEvent::IE_Released, this, &AWarPlayerController::OnTestMotionReleased);
}

void AWarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	myCharacter_ = Cast<APlayerCharacter>(GetCharacter());

	if (myCharacter_ == nullptr)
	{
		ABLOG(Error, TEXT("My Character Object nullptr!"));
	}

	//Player Input Mode에 연결 (까먹지 말기)
	SetInputMode(FInputModeGameOnly());
}

void AWarPlayerController::ZoomInStarted()
{
	zoomInBtn_ = true;
}

void AWarPlayerController::ZoomInReleased()
{
	zoomInBtn_ = false;
}

//구르기 모션
void AWarPlayerController::DiveJump()
{
	myCharacter_->PlayMontageDiveJump();
	ABLOG(Warning, TEXT("It's Dive Jump!!! %f"), myCharacter_->GetActorLocation().X);
}

//뛰기 모션
void AWarPlayerController::RunSprintStart()
{
	sprintBtn_ = true;
}

void AWarPlayerController::RunSprintReleased()
{
	sprintBtn_ = false;
}

//Test
void AWarPlayerController::OnTestMotionStart()
{
	testBtn_ = true;
}

void AWarPlayerController::OnTestMotionReleased()
{
	testBtn_ = false;
}

//공격(RayCast)
void AWarPlayerController::OnFireStart()
{
	fireBtn_ = true;
}

void AWarPlayerController::OnFireReleased()
{
	fireBtn_ = false;
}

bool AWarPlayerController::GetFireBtn()
{
	return fireBtn_;
}