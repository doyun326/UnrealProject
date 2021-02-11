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

	UPROPERTY()
		bool	state_;
	UPROPERTY()
		int32	npcID_;
	UPROPERTY()
		int32	conversation_;
	UPROPERTY()
		int32	currentLine_;
	UPROPERTY()
		TArray<FName>	myDialouge_;


protected:
	virtual void BeginPlay() override;

private:
	void	DialogueCreate();

	UPROPERTY(VisibleAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* terminalMesh_;
	
	struct FNpcDialogueData*	dialogueData_ = nullptr;

};
