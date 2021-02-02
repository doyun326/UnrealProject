// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/CharacterStatComponent.h"
#include "../Public/GameSetting/WarGameInstance.h"

UCharacterStatComponent::UCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	level_ = 1;
}

void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetNewLevel(level_);
}

void UCharacterStatComponent::SetNewLevel(int32 _newLevel)
{
	auto WarGameInstance = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (WarGameInstance == nullptr)
	{
		ABLOG(Warning, TEXT("Nullptr : WarGameInstance"));
		return;
	}

	level_ = _newLevel;
}

void UCharacterStatComponent::SetHp(float _newHp)
{
	currentHP_ = _newHp;
}

void UCharacterStatComponent::SetDamage(float _newDamage)
{

}

float UCharacterStatComponent::GetDamage()
{
	return 0.0f;
}

float UCharacterStatComponent::GetHpRatio()
{
	return 0.0f;
}
