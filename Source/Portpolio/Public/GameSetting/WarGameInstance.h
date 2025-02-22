// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Containers/CircularQueue.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "WarGameInstance.generated.h"

#define QUEUE_MAX 64

DECLARE_MULTICAST_DELEGATE(FOnViewWidget);
DECLARE_MULTICAST_DELEGATE(FOnViewWidget02);
DECLARE_MULTICAST_DELEGATE(FOnFlashEffect);
DECLARE_MULTICAST_DELEGATE(FOnLimitEffect);
DECLARE_MULTICAST_DELEGATE(FOnChangeExp);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeSequence, bool);

/*
* PlayerData
*/
USTRUCT(BlueprintType)
struct FPlayerData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FPlayerData() :
		Level(1)
		, MaxHP(300.0f)
		, MaxMP(300.0f)
		, Damage(25.0f)
		, NextExp(30)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		int32	Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		float	MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		float	MaxMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		float	Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerData")
		int32	NextExp;
};

/*
* ADEnemyData
*/
USTRUCT(BlueprintType)
struct FADEnemyData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FADEnemyData() :
		Level(1)
		, MaxHP(100.0f)
		, Damage(100.0f)
		, DropExp(10)
		, NextExp(30)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyData")
		int32	Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyData")
		float	MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyData")
		float	Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyData")
		int32	DropExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyData")
		int32	NextExp;
};

/*
* MinionData(ADEnemyData 사용)
*/
USTRUCT(BlueprintType)
struct FMinionEnemyData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FMinionEnemyData() :
		Level(1)
		, MaxHP(100.0f)
		, Damage(100.0f)
		, DropExp(10)
		, NextExp(30)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinionData")
		int32	Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinionData")
		float	MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinionData")
		float	Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinionData")
		int32	DropExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinionData")
		int32	NextExp;
};

/*
* BossData(BossData 사용)
*/
USTRUCT(BlueprintType)
struct FBossEnemyData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FBossEnemyData() :
		Level(1)
		, MaxHP(100.0f)
		, Damage(100.0f)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinionData")
		int32	Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinionData")
		float	MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinionData")
		float	Damage;
};

/*
* Dialogue Structor(Npc대화용 자막)
*/
USTRUCT(BlueprintType)
struct FNpcDialogueData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FNpcDialogueData() :
		NpcID(1)
		, Conversation(1)
		, LineID(1)
		, Dialogue(TEXT(""))
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		int32	NpcID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		int32	Conversation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		int32	LineID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		FString	Dialogue;
};

/**
 * 
 */ 
UCLASS()
class PORTPOLIO_API UWarGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UWarGameInstance();

	virtual void	Init() override;
	
	void	SetCheckAddViewport(bool _check);
	bool	GetCheckAddViewport();
	void	ReserveShakeCamera(int32 _count = 0);
	void	ShakeCamera();
	void	StageViewWidgetStart(FString _name);
	void	ActiveFlashEffect();
	void	ActiveLimitEffect();
	void	SetSaveExp(int32 _newExp);
	int32	GetSaveExp();
	void	SetPlayingSequence(bool _isplaying);
	bool	GetPlayingSequence();
	void	SetPlayerLevel(int32 _level);
	int32	GetPlayerLevel();
	
	//EnemyData
	FADEnemyData*		GetADEnemyData(int32 _level);
	FMinionEnemyData*	GetMinionEnemyData(int32 _level);
	FBossEnemyData*		GetBossEnemyData(int32 _level);

	//PlayerData
	FPlayerData*		GetPlayerData(int32 _level);

	//Dialogue Data
	FNpcDialogueData*	GetDialogueData(int32 _npcID);
	int32				GetDialogueRowNums();

	UPROPERTY(EditAnywhere, Category = "Camera")
		TSubclassOf<UCameraShake>	myShake_;

	FOnViewWidget		onViewWidget;
	FOnViewWidget02		onViewWidget02;
	FOnFlashEffect		onFlashEffect;
	FOnLimitEffect		onLimitEffect;
	FOnChangeExp		onChangeExp;
	FOnChangeSequence	onChangeSeqence;

private:
	UPROPERTY()
		class UDataTable*	adEnemyTable_;
	UPROPERTY()
		class UDataTable*	playerTable_;
	UPROPERTY()
		class UDataTable*	minionTable_;
	UPROPERTY()
		class UDataTable*	bossTable_;
	UPROPERTY()
		class UDataTable*	dialougeTable_;

	bool			viewCheck_;
	bool			sequenceCheck_;
	FTimerHandle	reserveTiemrHandler_;
	int32			checkCount_;
	int32			shakeCount_;
	int32			currentExp_ = 0;
	int32			currentPlayerlevel_;
	TCircularQueue<int32> expArray_{ QUEUE_MAX };
};
