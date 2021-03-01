// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/GameSetting/DialogueMaker.h"

// Sets default values
ADialogueMaker::ADialogueMaker()
{
	PrimaryActorTick.bCanEverTick = true;

	asxd = 0;
}

void ADialogueMaker::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADialogueMaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADialogueMaker::Test()
{
	asxd++;
	ABLOG(Error, TEXT("%d"), asxd);
}

