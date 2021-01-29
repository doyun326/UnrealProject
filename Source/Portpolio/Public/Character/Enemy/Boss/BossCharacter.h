// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Character/BaseCharacter.h"
#include "BossCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackFirEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackSecEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackThiEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHitEndDelegate);

/**
 * 
 */
UCLASS()
class PORTPOLIO_API ABossCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABossCharacter();

	virtual void	Tick(float DeltaTime) override;
	virtual void	SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void	PostInitializeComponents() override;
	virtual void	PossessedBy(AController* NewController) override;
	virtual float	TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void	FirstAttack();
	void	FirstAttackStop();
	void	SecondAttack();
	void	SecondAttackStop();
	void	ThirdAttack();
	void	ThirdAttackStop();
	void	HitStop();

	bool	GetFirstAttacking();
	bool	GetSecondAttacking();
	bool	GetThirdAttacking();
	bool	GetIsHiting();

	FOnAttackFirEndDelegate	OnAttackFirEnd;
	FOnAttackSecEndDelegate	OnAttackSecEnd;
	FOnAttackThiEndDelegate	OnAttackThiEnd;
	FOnHitEndDelegate		OnHitEnd;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class UBossAnimInstance* bossAnim_;

	bool	isFirstAttack_;
	bool	isSecondAttack_;
	bool	isThirdAttack_;
	bool	isHiting_;
};
