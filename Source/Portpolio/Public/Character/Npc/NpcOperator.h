// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting//Portpolio.h"

#include "Character/BaseCharacter.h"
#include "NpcOperator.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API ANpcOperator : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	ANpcOperator();

	virtual void	Tick(float DeltaTime) override;
	virtual void	PostInitializeComponents() override;
	virtual void	PossessedBy(AController* NewController) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = "UI")
		class UWidgetComponent* pressWidgetComponent_;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* collisionSphere_;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class UNpcOperatorAnimInstance* operAnim_;
	UPROPERTY()
		class UUserWidget* pressWidget_;

	bool	isTouch_;
};
