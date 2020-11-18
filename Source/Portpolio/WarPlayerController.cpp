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

	InputComponent->BindAction(TEXT("DiveJump"), EInputEvent::IE_Pressed, this, &AWarPlayerController::DiveJump);
}

void AWarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	myCharacter_ = Cast<APlayerCharacter>(GetCharacter());
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
		myCharacter_->SetActorLocation(FVector(myCharacter_->GetActorLocation().X + 100.0f, myCharacter_->GetActorLocation().Y, myCharacter_->GetActorLocation().Z));
	}
}