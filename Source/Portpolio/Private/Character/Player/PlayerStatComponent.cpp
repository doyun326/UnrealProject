// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Player/PlayerStatComponent.h"
#include "../Public/GameSetting/WarGameInstance.h"

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
	
}

void UPlayerStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetNewLevel(currentLevel_);
}

void UPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerStatComponent::SetNewLevel(int32 _newLevel)
{
	auto WarGameInstance = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (WarGameInstance == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarGameInstance"));
		return;
	}

	currentStatData_ = WarGameInstance->GetPlayerData(_newLevel);

	if (currentStatData_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : currentStatData"));
		return;
	}

	currentLevel_ = _newLevel;

	SetHp(currentStatData_->MaxHP);
	currentHP_ = currentStatData_->MaxHP;
	SetMp(currentStatData_->MaxMP);
	currentMP_ = currentStatData_->MaxMP;
	SetDamage(currentStatData_->Damage);
	currentDamage_ = currentStatData_->Damage;
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

void UPlayerStatComponent::SetMp(float _newMp)
{
	currentMP_ = _newMp;
	onMpChanged_.Broadcast();

	if (currentMP_ < KINDA_SMALL_NUMBER)
	{
		currentMP_ = 0.0f;
	}
}

void UPlayerStatComponent::SetExp(int32 _newExp)
{
	currentEXP_ = _newExp;
}

void UPlayerStatComponent::SetDamage(float _newDamage)
{
	currentDamage_ = _newDamage;
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

float UPlayerStatComponent::GetHpText()
{
	return currentHP_;
}

float UPlayerStatComponent::GetMpRatio()
{
	if (currentStatData_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : currentStatData"));
		return 0.0f;
	}
	return (currentStatData_->MaxMP < KINDA_SMALL_NUMBER) ? 0.0f : (currentMP_ / currentStatData_->MaxMP);
}

float UPlayerStatComponent::GetMpText()
{
	return currentMP_;
}

int32 UPlayerStatComponent::GetDamageRatio()
{
	return currentDamage_;
}