// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BossStatComponent.h"

UBossStatComponent::UBossStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UBossStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UBossStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

