// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Minion/EnemyMinionCharacter.h"

AEnemyMinionCharacter::AEnemyMinionCharacter()
{

}

void AEnemyMinionCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemyMinionCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyMinionCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEnemyMinionCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void AEnemyMinionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AEnemyMinionCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return FinalDamage;
}

void AEnemyMinionCharacter::EnemyDestroy()
{
	Destroy();
}