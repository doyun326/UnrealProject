// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Character/BaseCharacter.h"
#include "EnemyMinionCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AEnemyMinionCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyMinionCharacter();

	virtual void	Tick(float DeltaTime) override;
	virtual void	SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void	PostInitializeComponents() override;
	virtual void	PossessedBy(AController* NewController) override;
	virtual float	TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void	EnemyDestroy();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class UMinionAnimInstance* minionAnim_;
};
