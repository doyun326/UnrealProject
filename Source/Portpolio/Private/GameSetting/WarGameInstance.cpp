// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/GameSetting/WarGameInstance.h"

#define ADENEMYDT_PATH "/Game/My/GameData/ADEnemyData.ADEnemyData"
#define PLAYERDT_PATH "/Game/My/GameData/PlayerData.PlayerData"

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
	static ConstructorHelpers::FObjectFinder<UDataTable> ENEMY_DT(TEXT(ADENEMYDT_PATH));
	if (ENEMY_DT.Succeeded())
	{
		minionTable_ = ENEMY_DT.Object;
		ABLOG(Warning, TEXT("Success : EnemyTable"));
	}
}

void UWarGameInstance::Init()
{
	Super::Init();

	ABLOG(Warning, TEXT("Drop Exp of Leve"));
}

FADEnemyData* UWarGameInstance::GetADEnemyData(int32 _level)
{
	return adEnemyTable_->FindRow<FADEnemyData>(*FString::FromInt(_level), TEXT(""));
}

FPlayerData* UWarGameInstance::GetPlayerData(int32 _level)
{
	return playerTable_->FindRow<FPlayerData>(*FString::FromInt(_level), TEXT(""));
}

FMinionEnemyData* UWarGameInstance::GetMinionEnemyData(int32 _level)
{
	return minionTable_->FindRow<FMinionEnemyData>(*FString::FromInt(_level), TEXT(""));
}