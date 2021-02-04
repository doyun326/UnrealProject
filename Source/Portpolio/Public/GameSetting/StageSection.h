// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "GameFramework/Actor.h"
#include "StageSection.generated.h"

UCLASS()
class PORTPOLIO_API AStageSection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStageSection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
