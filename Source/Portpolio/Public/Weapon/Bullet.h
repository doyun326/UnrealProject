// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class PORTPOLIO_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetFormation(FVector _playerAimVector);
	 
	UPROPERTY(EditAnywhere)
		FVector Velocity = FVector(100.0f);
	UPROPERTY()
		class AWarPlayerController* playerController_;

	USceneComponent* RootComp;
	float bulletExpiry_ = 0.0f;

private:
	FVector bulletEndVector_;
	
	UPROPERTY()
	class AGunWeapon* weapon_;
};
