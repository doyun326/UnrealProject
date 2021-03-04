// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Character/BaseCharacter.h"
#include "BossCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFistAttackDelegate, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSecondAttackDelegate, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnThirdAttackDelegate, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHitDelegate, bool);

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

	void	SetEnemyState(ECharacterState _newState);

	void	ChangeFirstAttack(bool _attack);
	void	ChangeSecondAttack(bool _attack);
	void	ChangeThirdAttack(bool _attack);
	void	ChangeHit(bool _hit);

	bool	GetFirstAttacking();
	bool	GetSecondAttacking();
	bool	GetThirdAttacking();
	bool	GetIsHiting();
	void	BossDestroy();

	UPROPERTY()
		class ABossAIController* enemyController_;
	UPROPERTY(EditAnywhere, Category = "UI")
		class UWidgetComponent* HPBarWidget_;
	UPROPERTY(VisibleAnywhere, Category = "Stat")
		class UBossStatComponent* enemyStat_;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true))
		ECharacterState			currentState_;

	FOnFistAttackDelegate	onFirstAttack_;
	FOnFistAttackDelegate	onSecondAttack_;
	FOnFistAttackDelegate	onThirdAttack_;
	FOnHitDelegate			onHit_;

protected:
	virtual void BeginPlay() override;

private:
	void	NoDamageTime();

	UPROPERTY()
		class UBossAnimInstance* bossAnim_;
	UPROPERTY()
		class UBossHPWidget*	bossHpWidget_;

	bool	isFirstAttack_;
	bool	isSecondAttack_;
	bool	isThirdAttack_;
	bool	isHiting_;
	bool	isDamageTime_;

	FTimerHandle	noDamageTimeHandler_;
};
