// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Character/Player/WarPlayerController.h"
#include "../Public/Character/Player/PlayerAnimInstance.h"
#include "../Public/UI//PlayerHudWidget.h"
#include "../Public/Character/Player/WarPlayerState.h"
#include "../Public/GameSetting/WarGameInstance.h"

#include "Engine/Engine.h"

#define PLAYERHUD_WIDGET "/Game/My/Blueprints/UI/PlayerStausBar_UI.PlayerStausBar_UI_C"

AWarPlayerController::AWarPlayerController()
{
	//Player Widget
	static ConstructorHelpers::FClassFinder<UPlayerHudWidget> PLAYER_HUD(TEXT(PLAYERHUD_WIDGET));

	if (PLAYER_HUD.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : UI_HUD"));
		hudWidgetClass_ = PLAYER_HUD.Class;
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

	if (myPlayer_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : myCharacter"));
		return;
	}

	//Mouse Zoom In/out
	if (zoomInBtn_old && (zoomInBtn_old == zoomInBtn_))
	{
		myPlayer_->SetViewMode(ViewMode::ZOOMIN);
	}
	else
	{	
		myPlayer_->SetViewMode(ViewMode::COMMONVIEW);
	}

	//RayCast Hit and fire
	if (fireBtn_old && (fireBtn_old == fireBtn_))
	{
		myPlayer_->OnFire(true);
	}
	else
	{
		myPlayer_->OnFire(false);
	}

	//sprint
	if (sprintBtn_old && (sprintBtn_old == sprintBtn_))
	{
		myPlayer_->SetSprintBtn(true);
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = SPRINT_SPEED;
	}
	else
	{
		myPlayer_->SetSprintBtn(false);
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = WALK_SPEED;
	}
}

void AWarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	warInstance_ = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (warInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarInstance_"));
		return;
	}
	warInstance_->onChangeExp.AddUObject(this, &AWarPlayerController::UpdateExp);

	myPlayer_ = Cast<APlayerCharacter>(GetCharacter());

	if (myPlayer_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : myCharacter"));
	}

	//Player Input Mode에 연결
	SetInputMode(FInputModeGameOnly());

	if (hudWidgetClass_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : hudWidgetClass_"))
		return;
	}

	hudWidget_ = CreateWidget<UPlayerHudWidget>(this, hudWidgetClass_);
	hudWidget_->AddToViewport();

	myPlayerState_ = Cast<AWarPlayerState>(myPlayer_->GetPlayerState());

	if (hudWidget_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : hudWidget"));
		return;
	}

	if (myPlayerState_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : myPlayerState"));
		return;
	}

	hudWidget_->BindWarPlayerState(myPlayerState_);
	myPlayerState_->onPlayerStateChange.Broadcast();
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

	InputComponent->BindAction(TEXT("Avoid"), EInputEvent::IE_Pressed, this, &AWarPlayerController::OnAvoid);

	InputComponent->BindAction(TEXT("InfinityMode"), EInputEvent::IE_Pressed, this, &AWarPlayerController::OnInfinityMode);
}

void AWarPlayerController::OnAvoid()
{
	myPlayer_->PlayFlashEffect();
}

void AWarPlayerController::OnInfinityMode()
{
	myPlayer_->InfinityMode();
}

void AWarPlayerController::UpdateExp()
{
	if (myPlayerState_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : PlayerState"));
		return;
	}
	myPlayerState_->AddExp(warInstance_->GetSaveExp());
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
	ABLOG(Warning, TEXT("It's Dive Jump!!! %f"), myPlayer_->GetActorLocation().X);
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

void AWarPlayerController::HideHUD()
{
	hudWidget_->SetVisibility(ESlateVisibility::Hidden);
}

void AWarPlayerController::ShowHUD()
{
	hudWidget_->SetVisibility(ESlateVisibility::Visible);
}