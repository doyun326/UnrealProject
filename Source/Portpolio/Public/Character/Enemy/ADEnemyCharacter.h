// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Character/BaseCharacter.h"
#include "ADEnemyCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFistAttackDelegate, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSecondAttackDelegate, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHitDelegate, bool);

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AADEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AADEnemyCharacter();

	virtual void	Tick(float DeltaTime) override;
	virtual void	SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void	PostInitializeComponents() override;
	virtual void	PossessedBy(AController* NewController) override;
	virtual float	TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void			EnemyDestroy();
	void			SetEnemyState(ECharacterState _newState);
	int32			GetExp() const;
	ECharacterState	GetEnemyState() const;

	void	ChangeFirstAttack(bool _attack);
	void	ChangeSecondAttack(bool _attack);
	void	ChangeHit(bool _hit);

	bool	GetFirstAttacking();
	bool	GetSecondAttacking();
	bool	GetIsHiting();

	UPROPERTY()
		class AADAIController*			enemyController_;
	UPROPERTY(EditAnywhere, Category = "UI")
		class UWidgetComponent*			HPBarWidget_;
	UPROPERTY(VisibleAnywhere, Category = "Stat")
		class UADEnemyStatComponent*	enemyStat_;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true))
		ECharacterState					currentState_;

	FOnFistAttackDelegate	onFirstAttack_;
	FOnFistAttackDelegate	onSecondAttack_;
	FOnHitDelegate			onHit_;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void	AttackCheck();

	UPROPERTY()
		class UADAnimInstance* ADAnim_;
	UPROPERTY()
		class UEnemyHPWidget* EnemyHpWidget_;

	bool	isFirstAttack_;
	bool	isSecondAttack_;
	bool	isThirdAttack_;
	bool	isHiting_;
};
