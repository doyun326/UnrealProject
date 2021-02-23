// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "Components/ActorComponent.h"
#include "PlayerStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHpChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMpChangeDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTPOLIO_API UPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStatComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void	SetNewLevel(int32 _newLevel);
	//void	SetLimitLevel();
	void	SetHp(float _newHp);
	void	SetMp(float _newMp);
	void	SetExp(int32 _newExp);
	void	SetDamage(float _newDamage);
	float	GetHpRatio();
	float	GetHpText();
	float	GetMpRatio();
	float	GetMpText();
	int32	GetDamageRatio();

	FOnHpChangeDelegate onHpChanged_;
	FOnMpChangeDelegate onMpChanged_;
	FOnHpZeroDelegate	onHpIsZero_;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

private:
	struct FPlayerData* currentStatData_ = nullptr;

	UPROPERTY(EditInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
		int32 currentLevel_;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
		float currentHP_;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
		float currentMP_;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
		float currentDamage_;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", meta = (AllowPrivateAccess = true))
		int32 currentEXP_;
		
};