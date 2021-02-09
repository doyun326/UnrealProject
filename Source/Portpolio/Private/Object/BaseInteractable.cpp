// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Object/BaseInteractable.h"

ABaseInteractable::ABaseInteractable()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComponent_ = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = rootComponent_;

	mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh_->SetupAttachment(RootComponent);
}

void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

