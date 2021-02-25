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
	AStageSection();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

private:
	enum class ESectionState : uint8
	{
		READY = 0,
		BATTLE,
		COMPLATE
	};

	UFUNCTION()
		void	OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void	OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	void	SetState(ESectionState _newState);
	void	OperatorGates(bool _bOpen = true);

	UPROPERTY(VisibleAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent*			mapMesh_;
	UPROPERTY(VisibleAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = true))
		TArray<UStaticMeshComponent*>	gateMeshs_;
	UPROPERTY(VisibleAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent*			celingMeshs_;

	UPROPERTY(VisibleAnywhere, Category = "Trigger", meta = (AllowPrivateAccess = true))
		UBoxComponent*			startTrigger_;
	UPROPERTY(VisibleAnywhere, Category = "Trigger", meta = (AllowPrivateAccess = true))
		TArray<UBoxComponent*>	gateTriggers_;
	UPROPERTY(VisibleAnywhere, Category = "State", meta = (AllowPrivateAccess = true))
		bool	bNoBattle_;
		
	ESectionState currentState_ = ESectionState::READY;
};
