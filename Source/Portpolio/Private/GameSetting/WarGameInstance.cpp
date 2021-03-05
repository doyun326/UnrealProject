// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/GameSetting/WarGameInstance.h"
#include "../Public/GameSetting/MyCameraShake.h"
#include "../Public/Character/Player/WarPlayerController.h"

#include "Containers/CircularQueue.h"

#define ADENEMYDT_PATH			"/Game/My/GameData/ADEnemyData.ADEnemyData"
#define PLAYERDT_PATH			"/Game/My/GameData/PlayerData.PlayerData"
#define MINIONDT_PATH			"/Game/My/GameData/MinionEnemyData.MinionEnemyData"
#define DIALOGUE_PATH			"/Game/My/GameData/NpcDialogue.NpcDialogue"
#define BOSSDATA_PATH			"/Game/My/GameData/BossData.BossData"
#define CAMERASHAKECLASS_PATH	"/Script/Portpolio.MyCameraShake"

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

	//BossData
	static ConstructorHelpers::FObjectFinder<UDataTable> BOSS_DT(TEXT(BOSSDATA_PATH));

	if (BOSS_DT.Succeeded())
	{
		bossTable_ = BOSS_DT.Object;
		ABLOG(Warning, TEXT("Success : BossTable"));
	}

	//NpcDialogueData
	static ConstructorHelpers::FObjectFinder<UDataTable> DIALOGUE_DT(TEXT(DIALOGUE_PATH));

	if (DIALOGUE_DT.Succeeded())
	{
		dialougeTable_ = DIALOGUE_DT.Object;
		ABLOG(Warning, TEXT("Success : DialogueTable"));
	}

	//ShakeCamera Setting
	static ConstructorHelpers::FClassFinder<UCameraShake> CAMERA_SHAKE(TEXT(CAMERASHAKECLASS_PATH));

	if (CAMERA_SHAKE.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : CAMERA_SHAKE"));
		myShake_ = (UClass*)CAMERA_SHAKE.Class;
	}

	viewCheck_ = false;
	sequenceCheck_ = false;
	checkCount_ = 0;
	shakeCount_ = 0;
	currentExp_ = 0;
	expArray_.Empty();
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

FBossEnemyData* UWarGameInstance::GetBossEnemyData(int32 _level)
{
	if (bossTable_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : bossTable"));
		return nullptr;
	}

	return bossTable_->FindRow<FBossEnemyData>(*FString::FromInt(_level), TEXT(""));
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

void UWarGameInstance::ReserveShakeCamera(int32 _count)
{
	if (_count == 0)
	{
		GetWorld()->GetTimerManager().SetTimer(reserveTiemrHandler_, this, &UWarGameInstance::ShakeCamera, 2.0f, false);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(reserveTiemrHandler_, this, &UWarGameInstance::ShakeCamera, 2.0f, true);
		checkCount_ = _count;
	}
}

void UWarGameInstance::ShakeCamera()
{
	if (GetWorld() == nullptr || myShake_ == nullptr)
	{
		ABLOG(Error, TEXT("Error : ShakeCamera"));
		return;
	}
	ABLOG(Error, TEXT("ShakeCamera"));
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(myShake_, 0.3f);

	if (checkCount_ != 0)
	{
		shakeCount_++;
	}
	if (shakeCount_ == checkCount_)
	{
		GetWorld()->GetTimerManager().ClearTimer(reserveTiemrHandler_);
	}
}

void UWarGameInstance::StageViewWidgetStart(FString _name)
{
	if (_name == "Stage_01")
	{
		onViewWidget.Broadcast();
	}
	if (_name == "Stage_02")
	{
		onViewWidget02.Broadcast();
	}
}

void UWarGameInstance::ActiveFlashEffect()
{
	onFlashEffect.Broadcast();
}

void UWarGameInstance::ActiveLimitEffect()
{
	onLimitEffect.Broadcast();
}

void UWarGameInstance::SetSaveExp(int32 _newExp)
{
	expArray_.Enqueue(_newExp);
	ABLOG(Error, TEXT("%d"), expArray_.Count());
	onChangeExp.Broadcast();
}

int32 UWarGameInstance::GetSaveExp()
{
	if (expArray_.IsEmpty())
	{
		return 0.0f;
	}
	currentExp_ = *expArray_.Peek();
	expArray_.Dequeue();

	return currentExp_;
}

void UWarGameInstance::SetPlayingSequence(bool _isplaying)
{
	sequenceCheck_ = _isplaying;
}

bool UWarGameInstance::GetPlayingSequence()
{
	return sequenceCheck_;
}