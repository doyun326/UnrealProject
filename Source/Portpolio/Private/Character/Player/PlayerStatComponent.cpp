// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Player/PlayerStatComponent.h"
#include "../Public/GameSetting/WarGameInstance.h"

// Sets default values for this component's properties
UPlayerStatComponent::UPlayerStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	currentLevel_ = 1;
}


// Called when the game starts
void UPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPlayerStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetNewLevel(currentLevel_);

}


// Called every frame
void UPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerStatComponent::SetNewLevel(int32 _newLevel)
{
	auto WarGameInstance = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (WarGameInstance == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarGameInstance"));
		return;
	}

	currentStatData_ = WarGameInstance->GetADEnemyData(_newLevel);

	if (currentStatData_ != nullptr)
	{
		currentLevel_ = _newLevel;
		SetHp(currentStatData_->MaxHP);
		currentHP_ = currentStatData_->MaxHP;
	}
	else
	{
		ABLOG(Error, TEXT("Nullptr : currentStatData"));
	}
}

void UPlayerStatComponent::SetHp(float _newHp)
{
	currentHP_ = _newHp;
	onHpChanged_.Broadcast();

	if (currentHP_ < KINDA_SMALL_NUMBER)
	{
		currentHP_ = 0.0f;
	}
}

float UPlayerStatComponent::GetHpRatio()
{
	if (currentStatData_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : currentStatData"));
		return 0.0f;
	}
	return (currentStatData_->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (currentHP_ / currentStatData_->MaxHP);
}