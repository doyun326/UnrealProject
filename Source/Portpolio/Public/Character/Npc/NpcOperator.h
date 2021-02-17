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

	void	LevelStart();
	void	DialogueCreate();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* collisionSphere_;
	UPROPERTY(EditAnywhere, Category = "UI")
		class UWidgetComponent* dialogueWidgetClass_;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class UNpcOperatorAnimInstance* operAnim_;
	UPROPERTY()
		class UAIDeskInteractionWidget* dialougeWidget_;
	UPROPERTY()
		class UWarGameInstance*			WarInstance_;
	UPROPERTY()
		int32	npcID_;
	UPROPERTY()
		int32	conversation_;
	UPROPERTY()
		int32	currentLineID_;
	UPROPERTY()
		TArray<FString>	dialougeTexts_;

	TArray<struct FNpcDialogueData*>	dialogueDatas_;

	FTimerHandle	viewTimeHandler_;
	bool			addViewportCheck_;
	int32			rowNum_;
};
