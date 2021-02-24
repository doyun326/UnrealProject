// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Engine/LevelScriptActor.h"
#include "Stage01LevelScript.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AStage01LevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	AStage01LevelScript();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USceneComponent*			rootComponent_;

protected:
	virtual void BeginPlay();

private:
	UFUNCTION()
		void	OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void	OnNextMapTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void	WidgetStart();

	UPROPERTY()
		class UWarGameInstance*		warInstance_;
	UPROPERTY()
		class ULevelSequencePlayer*	sequencePlayer_;
	UPROPERTY(EditAnywhere)
		class ULevelSequence*		sequenceAsset_;
	UPROPERTY(VisibleAnywhere, Category = "Trigger", meta = (AllowPrivateAccess = true))
		UBoxComponent*				walkTrigger_;
	UPROPERTY(VisibleAnywhere, Category = "Trigger", meta = (AllowPrivateAccess = true))
		UBoxComponent*				nextMapTrigger_;

	FTimerHandle	startWidgetHandler_;

	bool	checkGo_;
};
