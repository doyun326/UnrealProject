// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Character/Enemy/ADEnemyStatComponent.h"
#include "../Public/GameSetting/WarGameInstance.h"

// Sets default values for this component's properties
UADEnemyStatComponent::UADEnemyStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	level_ = 1;
}

// Called when the game starts
void UADEnemyStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UADEnemyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetNewLevel(level_);
}

// Called every frame
void UADEnemyStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UADEnemyStatComponent::SetNewLevel(int32 _newLevel)
{
	auto WarGameInstance = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (WarGameInstance == nullptr)
	{
		ABLOG(Warning, TEXT("WarGameInstance is nullptr"));
		return;
	}

	currentStatData_ = WarGameInstance->GetADEnemyData(_newLevel);

	if (currentStatData_ != nullptr)
	{
		level_ = _newLevel;
		SetHp(currentStatData_->MaxHP);
		currentHP_ = currentStatData_->MaxHP;
	}
	else
	{
		ABLOG(Error, TEXT("Level : %d data dosn't exit"));
	}
}

void UADEnemyStatComponent::SetHp(float _newHp)
{
	currentHP_ = _newHp;
	onHpChanged_.Broadcast();

	if (currentHP_ < KINDA_SMALL_NUMBER)
	{
		currentHP_ = 0.0f;
		//onHpChanged_
	}
}

float UADEnemyStatComponent::GetHpRatio()
{
	if (currentStatData_ == nullptr)
	{
		ABLOG(Warning, TEXT("currentStatData is nullptr"));
		return 0.0f;
	}
	return (currentStatData_->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (currentHP_ / currentStatData_->MaxHP);
}