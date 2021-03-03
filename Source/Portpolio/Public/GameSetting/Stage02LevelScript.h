// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Engine/LevelScriptActor.h"
#include "Stage02LevelScript.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AStage02LevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	AStage02LevelScript();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USceneComponent* rootComponent_;

protected:
	virtual void BeginPlay();

private:
	UFUNCTION()
		void	OnBeginStartTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void	OnLevelUpTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
		class UWarGameInstance* warInstance_;
	UPROPERTY(VisibleAnywhere, Category = "Trigger", meta = (AllowPrivateAccess = true))
		UBoxComponent*			beginStartTrigger_;
	UPROPERTY(VisibleAnywhere, Category = "Trigger", meta = (AllowPrivateAccess = true))
		UBoxComponent*			stage02LevelUpTrigger_;

	bool checkStart_;
	bool checkLevelUp_;
};
