// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Minion/MinionEnemyStatComponent.h"

UMinionEnemyStatComponent::UMinionEnemyStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMinionEnemyStatComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UMinionEnemyStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

