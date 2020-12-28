// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/GameSetting/WarGameInstance.h"

#define ADENEMY_PATH "/Game/My/GameData/ADEnemyData.ADEnemyData"

UWarGameInstance::UWarGameInstance()
{
	//ADEnemyData
	static ConstructorHelpers::FObjectFinder<UDataTable> ADENEMY_DT(TEXT(ADENEMY_PATH));
	
	if (ADENEMY_DT.Succeeded())
	{
		adEnemyTable_ = ADENEMY_DT.Object;
		ABLOG(Warning, TEXT("ADEnemyTable is not nullptr"));
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