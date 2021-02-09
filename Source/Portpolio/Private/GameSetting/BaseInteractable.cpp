// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/GameSetting/BaseInteractable.h"

ABaseInteractable::ABaseInteractable()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

