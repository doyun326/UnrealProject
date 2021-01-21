// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Character/Player/WarPlayerController.h"
#include "../Public/Character/Player/PlayerAnimInstance.h"
#include "../Public/UI//PlayerHudWidget.h"

#include "Engine/Engine.h"

#define PLAYERHUD_WIDGET "/Game/My/Asset/UI/PlayerStausBar_UI.PlayerStausBar_UI_C"

AWarPlayerController::AWarPlayerController()
{
	//Player Widget
	static ConstructorHelpers::FClassFinder<UPlayerHudWidget> PLAYER_HUD(TEXT(PLAYERHUD_WIDGET));

	if (PLAYER_HUD.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : UI_HUD"));
		hudWidgetClass = PLAYER_HUD.Class;
	}

	zoomInBtn_ = false;
	sprintBtn_ = false;
	fireBtn_ = false;
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

	Super::ProcessPlayerInput(DeltaTime, bGamePaused);

	if (myCharacter_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : myCharacter"));
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
		myCharacter_->OnFire(true);
	}
	else
	{
		myCharacter_->OnFire(false);
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
}

void AWarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	myCharacter_ = Cast<APlayerCharacter>(GetCharacter());

	if (myCharacter_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : myCharacter"));
	}

	//Player Input Mode에 연결
	SetInputMode(FInputModeGameOnly());

	if (hudWidgetClass == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : hudWidgetClass"))
		return;
	}
	hudWidget_ = CreateWidget<UPlayerHudWidget>(this, hudWidgetClass);
	hudWidget_->AddToViewport();
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

class UPlayerHudWidget* AWarPlayerController::GetHudWidget() const
{
	return hudWidget_;
}