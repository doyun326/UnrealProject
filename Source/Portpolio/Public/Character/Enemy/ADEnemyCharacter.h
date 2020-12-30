// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "Character/BaseCharacter.h"
#include "ADEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AADEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AADEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(EditAnywhere, Category = UI)
		class UWidgetComponent*	HPBarWidget_;
	UPROPERTY(VisibleAnywhere, Category = Stat)
		class UADEnemyStatComponent* enemyStat_;

	class UWorld* test;

private:
};
