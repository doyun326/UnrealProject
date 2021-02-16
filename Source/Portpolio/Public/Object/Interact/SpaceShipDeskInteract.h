// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "Object/BaseInteractable.h"

#include "SpaceShipDeskInteract.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API ASpaceShipDeskInteract : public ABaseInteractable
{
	GENERATED_BODY()
	
public:
	ASpaceShipDeskInteract();

	virtual void Interact() override;

	void	GetDialogueLine();

	UPROPERTY()
		int32	npcID_;
	UPROPERTY()
		int32	conversation_;
	UPROPERTY()
		int32	currentLineID_;
	UPROPERTY()
		TArray<FString>	dialougeTexts_;

	UPROPERTY(EditAnywhere, Category = "UI")
		class UWidgetComponent* dialogueWidgetClass_;

protected:
	virtual void BeginPlay() override;

private:
	void	DialogueCreate();
	void	ChangeDialogue();
	void	RemoveWidget();

	UPROPERTY(VisibleAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent*				terminalMesh_;
	UPROPERTY()
		class UAIDeskInteractionWidget*		dialougeWidget_;
	UPROPERTY()
		class UWarGameInstance*				WarInstance_;

	TArray<struct FNpcDialogueData*>	dialogueDatas_;
	TArray<FString>						lineText_;

	FTimerHandle	viewTimeHandler_;
	bool			addViewportCheck_;
	int32			rowNum_;
};
