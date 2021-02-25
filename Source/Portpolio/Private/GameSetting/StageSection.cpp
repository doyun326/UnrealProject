// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/GameSetting/StageSection.h"
#include "../Public/GameSetting/WarGameMode.h"

#include "DrawDebugHelpers.h"

#define SQUAREMESH_PATH		"/Game/My/Asset/Map/SM_SQUARE.SM_SQUARE"
#define GATEMESH_PATH		"/Game/My/Asset/Map/SM_Plains_Castle_DemonDoor_01.SM_Plains_Castle_DemonDoor_01"
#define CELINGMESH_PATH		"/Game/InfinityBladeGrassLands/Environments/Misc/Exo_Deco02/StaticMesh/SM_Exo_Doorframe_02.SM_Exo_Doorframe_02"

AStageSection::AStageSection()
{
	PrimaryActorTick.bCanEverTick = false;

	//mapMesh Setting
	mapMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = mapMesh_;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SQUARE(TEXT(SQUAREMESH_PATH));

	if (SM_SQUARE.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : SM_SQUARE"));
		mapMesh_->SetStaticMesh(SM_SQUARE.Object);
	}
	mapMesh_->SetRelativeScale3D(FVector(2.0f, 2.0f, 5.0f));

	//Celing Setting
	celingMeshs_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CelingMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_CELING(TEXT(CELINGMESH_PATH));

	if (SM_CELING.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : SM_CELING"));
		celingMeshs_->SetStaticMesh(SM_CELING.Object);
	}
	celingMeshs_->SetupAttachment(RootComponent);
	celingMeshs_->SetRelativeLocation(FVector(0.0f, -1900.0f, 300.0f));
	celingMeshs_->SetRelativeRotation(FRotator(00.0f, 00.0f, 90.0f));
	celingMeshs_->SetRelativeScale3D(FVector(8.0f, 1.0f, 8.0f));

	//Trigger Setting (startTrigger)
	startTrigger_ = CreateDefaultSubobject<UBoxComponent>(TEXT("STARTTRIGGER"));
	startTrigger_->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));	//Trigger Box Extent(ºÎÇÇ)
	startTrigger_->SetupAttachment(RootComponent);
	startTrigger_->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f)); //Trigger Box Location
	startTrigger_->SetCollisionProfileName(TEXT("MapTrigger"));

	startTrigger_->OnComponentBeginOverlap.AddDynamic(this, &AStageSection::OnTriggerBeginOverlap);

	//gateMesh Setting
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DEMON_GATE(TEXT(GATEMESH_PATH));

	if (DEMON_GATE.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : DEMON_GATE"));
	}

	static FName GateSockets[] = { {TEXT("+XGate")}, {TEXT("-XGate")}, {TEXT("+YGate")}, {TEXT("-YGate")} };

	for (FName GateSocket : GateSockets)
	{
		if (!mapMesh_->DoesSocketExist(GateSocket))
		{
			ABLOG(Error, TEXT("DoesSocketExist : GateSocket"))
			return;
		}

		UStaticMeshComponent* NewGate = CreateDefaultSubobject<UStaticMeshComponent>(*GateSocket.ToString());
		NewGate->SetStaticMesh(DEMON_GATE.Object);
		NewGate->SetupAttachment(RootComponent, GateSocket);
		NewGate->SetRelativeLocation(FVector(18.0f, 0.0f, 0.0f));
		NewGate->SetRelativeRotation(FRotator(20.0f, 20.0f, 20.0f));
		NewGate->SetRelativeScale3D(FVector(1.8f, 1.8f, 1.5f));
		gateMeshs_.Add(NewGate);

		//Trigger Setting (gateTrigger)
		UBoxComponent* NewGateTrigger = CreateDefaultSubobject<UBoxComponent>(*GateSocket.ToString().Append(TEXT("startTrigger_")));

		NewGateTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		NewGateTrigger->SetupAttachment(RootComponent, GateSocket);
		NewGateTrigger->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		NewGateTrigger->SetCollisionProfileName(TEXT("MapTrigger"));
		gateTriggers_.Add(NewGateTrigger);

		NewGateTrigger->OnComponentBeginOverlap.AddDynamic(this, &AStageSection::OnGateTriggerBeginOverlap);
		NewGateTrigger->ComponentTags.Add(GateSocket);
	}
	bNoBattle_ = false;
}

void AStageSection::BeginPlay()
{
	Super::BeginPlay();
	
	SetState(bNoBattle_ ? ESectionState::COMPLATE : ESectionState::READY);
	//SetState(ESectionState::READY);
	//SetState(ESectionState::COMPLATE);
	//SetState(ESectionState::BATTLE);

	//StartTrigger
	//DrawDebugBox(GetWorld(), FVector(0.0f, 0.0f, 100.0f), FVector(100.0f, 100.0f, 100.0f), FColor::Red, true, -1, 0, 10);
}

void AStageSection::SetState(ESectionState _newState)
{
	switch (_newState)
	{
	case AStageSection::ESectionState::READY:
	{
		startTrigger_->SetCollisionProfileName(TEXT("MapTrigger"));

		for (UBoxComponent* GateTrigger : gateTriggers_)
		{
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}
		OperatorGates(true);
		ABLOG(Error, TEXT("ESectionState::READY"));
		break;
	}

	case AStageSection::ESectionState::BATTLE:
	{
		startTrigger_->SetCollisionProfileName(TEXT("NoCollision"));

		for (UBoxComponent* GateTrigger : gateTriggers_)
		{
			GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
		}
		OperatorGates(false);
		ABLOG(Error, TEXT("ESectionState::BATTLE"));
		break;
	}

	case AStageSection::ESectionState::COMPLATE:
	{
		startTrigger_->SetCollisionProfileName(TEXT("NoCollision"));

		for (UBoxComponent* GateTrigger : gateTriggers_)
		{
			GateTrigger->SetCollisionProfileName(TEXT("MapTrigger"));
		}
		//OperatorGates(true);
		OperatorGates(false);
		ABLOG(Error, TEXT("ESectionState::COMPLATE"));
		break;
	}
	}
	//currentState_ = _newState;
}

void AStageSection::OperatorGates(bool _bOpen)
{
	for(UStaticMeshComponent* Gate : gateMeshs_)
	{
		Gate->SetRelativeLocation(_bOpen ? FVector::ZeroVector : FVector(150.0f, 80.0f, 0.0f));
		Gate->SetRelativeRotation(_bOpen ? FRotator(0.0f, -90.0f, 0.0f) : FRotator::ZeroRotator);
	}
}

void AStageSection::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetState(bNoBattle_ ? ESectionState::COMPLATE : ESectionState::READY);
}

void AStageSection::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (currentState_ == ESectionState::READY)
	{
		//SetState(ESectionState::BATTLE);
		SetState(ESectionState::COMPLATE);
		ABLOG(Error, TEXT("Overlap On"));

	}
}

void AStageSection::OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComponent->ComponentTags.Num() != 1)
	{
		ABLOG(Error, TEXT("Tag's Error!!"));
		return;
	}

	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	FName SocketName = FName(*ComponentTag.ToString().Left(2));

	if (!mapMesh_->DoesSocketExist(SocketName))
	{
		ABLOG(Error, TEXT("Doesn't Socket Exist"));
		return;
	}

	FVector NewLocation = mapMesh_->GetSocketLocation(SocketName);
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FCollisionObjectQueryParams	ObjectQueryParam(FCollisionObjectQueryParams::InitType::AllObjects);
	
	bool bResult = GetWorld()->OverlapMultiByObjectType
	(
		OverlapResults,
		NewLocation,
		FQuat::Identity,
		ObjectQueryParam,
		FCollisionShape::MakeSphere(775.0f),
		CollisionQueryParam
	);

	DrawDebugSphere(GetWorld(), NewLocation, 775.0f, 16, FColor::Green, false, 0.2f);

	if (!bResult)
	{
		auto NewSocket = GetWorld()->SpawnActor<AStageSection>(NewLocation, FRotator::ZeroRotator);
		ABLOG(Error, TEXT("New Section Area is Extent"));
	}
	else
	{
		ABLOG(Error, TEXT("New Section Area is not empty"));
	}
	ABLOG(Error, TEXT("Overlap On"));
}