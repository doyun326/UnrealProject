// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/GameSetting/WarGameInstance.h"

#define ADENEMYDT_PATH		"/Game/My/GameData/ADEnemyData.ADEnemyData"
#define PLAYERDT_PATH		"/Game/My/GameData/PlayerData.PlayerData"
#define MINIONDT_PATH		"/Game/My/GameData/MinionEnemyData.MinionEnemyData"
#define DIALOGUE_PATH		"/Game/My/GameData/NpcDialogue.NpcDialogue"

UWarGameInstance::UWarGameInstance()
{
	//ADEnemyData
	static ConstructorHelpers::FObjectFinder<UDataTable> ADENEMY_DT(TEXT(ADENEMYDT_PATH));
	
	if (ADENEMY_DT.Succeeded())
	{
		adEnemyTable_ = ADENEMY_DT.Object;
		ABLOG(Warning, TEXT("Success : ADEnemyTable"));
	}

	//PlayerData
	static ConstructorHelpers::FObjectFinder<UDataTable> PLAYER_DT(TEXT(PLAYERDT_PATH));

	if (PLAYER_DT.Succeeded())
	{
		playerTable_ = PLAYER_DT.Object;
		ABLOG(Warning, TEXT("Success : PlayerTable"));
	}

	//MinionData(ADData »ç¿ë)
	static ConstructorHelpers::FObjectFinder<UDataTable> MINION_DT(TEXT(MINIONDT_PATH));

	if (MINION_DT.Succeeded())
	{
		minionTable_ = MINION_DT.Object;
		ABLOG(Warning, TEXT("Success : MinionTable"));
	}

	//NpcDialogueData
	static ConstructorHelpers::FObjectFinder<UDataTable> DIALOGUE_DT(TEXT(DIALOGUE_PATH));

	if (DIALOGUE_DT.Succeeded())
	{
		dialougeTable_ = DIALOGUE_DT.Object;
		ABLOG(Warning, TEXT("Success : DialogueTable"));
	}

	viewCheck_ = false;
}

void UWarGameInstance::Init()
{
	Super::Init();

	ABLOG(Warning, TEXT("Drop Exp of Leve"));
}

void UWarGameInstance::SetCheckAddViewport(bool _check)
{
	viewCheck_ = _check;
}

bool UWarGameInstance::GetCheckAddViewport()
{
	return viewCheck_;
}

FADEnemyData* UWarGameInstance::GetADEnemyData(int32 _level)
{
	if (adEnemyTable_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : ADEnemyTable"));
		return nullptr;
	}

	return adEnemyTable_->FindRow<FADEnemyData>(*FString::FromInt(_level), TEXT(""));
}

FPlayerData* UWarGameInstance::GetPlayerData(int32 _level)
{
	if (playerTable_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : PlayerTable"));
		return nullptr;
	}

	return playerTable_->FindRow<FPlayerData>(*FString::FromInt(_level), TEXT(""));
}

FMinionEnemyData* UWarGameInstance::GetMinionEnemyData(int32 _level)
{
	if (minionTable_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : MinionTable"));
		return nullptr;
	}

	return minionTable_->FindRow<FMinionEnemyData>(*FString::FromInt(_level), TEXT(""));
}

FNpcDialogueData* UWarGameInstance::GetDialogueData(int32 _npcID)
{
	if (dialougeTable_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : DialougeTable"));
		return nullptr;
	}

	return dialougeTable_->FindRow<FNpcDialogueData>(*FString::FromInt(_npcID), TEXT(""));
}

int32 UWarGameInstance::GetDialogueRowNums()
{
	return dialougeTable_->GetRowNames().Num();
}