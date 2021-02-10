// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Object/Interact/SpaceShipDeskInteract.h"

#define TERMINAL_MESH_PATH	"/Game/StarterBundle/ModularSci_Comm/Meshes/SM_Terminal_A_UI.SM_Terminal_A_UI"

ASpaceShipDeskInteract::ASpaceShipDeskInteract()
{
	//Mesh ¼³Á¤
	terminalMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalMesh"));
	RootComponent = terminalMesh_;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TERMINAL_MESH(TEXT(TERMINAL_MESH_PATH));

	if (TERMINAL_MESH.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : TerminalMesh"));
		terminalMesh_->SetStaticMesh(TERMINAL_MESH.Object);
	}

	state_ = false;
}

void ASpaceShipDeskInteract::BeginPlay()
{
	Super::BeginPlay();
}

void ASpaceShipDeskInteract::Interact()
{
	//Super::Interact();
	if (state_)
	{
		ABLOG(Warning, TEXT("State is true!"));
	}
	else
	{
		ABLOG(Warning, TEXT("State is false"));
	}
	state_ = !state_;
}