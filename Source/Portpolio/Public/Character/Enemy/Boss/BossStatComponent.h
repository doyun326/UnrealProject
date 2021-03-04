// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Components/ActorComponent.h"
#include "BossStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTPOLIO_API UBossStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBossStatComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void	SetNewLevel(int32 _newLevel);
	void	SetHp(float _newHp);
	void	SetDamage(float _newDamage);
	float	GetDamage();
	float	GetHpRatio();
	int32	GetLevel() const;

	FOnHpChangeDelegate onHpChanged_;
	FOnHpZeroDelegate	onHpZero_;

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

private:
	struct FBossEnemyData* currentStatData_ = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 level_;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, meta = (AllowPrivateAccess = true))
		float currentHP_;
};
