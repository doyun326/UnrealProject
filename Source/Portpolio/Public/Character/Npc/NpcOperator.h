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

	void	ViewWidget();
	void	DialogueCreate();
	void	ChangeDialogue();
	void	ControllPlayerEffect();
	void	RemoveWidget();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* collisionSphere_;
	UPROPERTY(EditAnywhere, Category = "UI")
		class UWidgetComponent* dialogueWidgetClass_;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
		int32	npcID_;
	UPROPERTY()
		int32	conversation_;
	UPROPERTY()
		int32	currentLineID_;
	UPROPERTY()
		class UAIDeskInteractionWidget* dialougeWidget_;
	UPROPERTY()
		class UWarGameInstance* warInstance_;
	UPROPERTY()
		TArray<FString>	dialougeTexts_;
	
	TArray<struct FNpcDialogueData*>	dialogueDatas_;

private:
	UPROPERTY()
		class UNpcOperatorAnimInstance* operAnim_;

	FTimerHandle	viewTimeHandler_;
	FTimerHandle	effectTimeHandler_;

	bool		addViewportCheck_;
	int32		rowNum_;
	int32		remainNum_;
	int32		effectCheck_;
};
