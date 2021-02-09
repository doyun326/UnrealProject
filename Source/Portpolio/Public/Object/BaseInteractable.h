// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

UCLASS()
class PORTPOLIO_API ABaseInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseInteractable();

	virtual void Tick(float DeltaTime) override;
	virtual void Interact() PURE_VIRTUAL(ABaseInteractable::Interact, )

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USceneComponent*		rootComponent_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMeshComponent*	mesh_;

protected: 
	virtual void BeginPlay() override;
	
private:

};
