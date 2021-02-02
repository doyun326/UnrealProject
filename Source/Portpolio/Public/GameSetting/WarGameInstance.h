// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "WarGameInstance.generated.h"

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
* MinionData(ADEnemyData ���)
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
	
	FADEnemyData*		GetADEnemyData(int32 _level);
	FMinionEnemyData*	GetMinionEnemyData(int32 _level);
	FPlayerData*		GetPlayerData(int32 _level);

private:
	UPROPERTY()
		class UDataTable* adEnemyTable_;
	UPROPERTY()
		class UDataTable* playerTable_;
	UPROPERTY()
		class UDataTable* minionTable_;
};
