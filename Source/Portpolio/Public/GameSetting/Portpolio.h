// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "defaults.h"

DECLARE_LOG_CATEGORY_EXTERN(Portpolio, Log, All);
#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define ABLOG_S(Verbosity) UE_LOG(Portpolio, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
#define ABLOG(Verbosity, Format, ...) UE_LOG(Portpolio, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define ABCHECK(Expr, ...) { if (!(Expr)) { ABLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; } }

#define SPRINT_SPEED 1200.0f
#define WALK_SPEED 700.0f

//그립 종류
#define REST_GRIPSOCKET		"RestGripPoint"
#define FIRE_GRIPSOCKET		"FireGripPoint"
#define SPRINT_GRIPSOCKET	"SprintGripPoint"
#define WALK_GRIPSOCKET		"WalkGripPoint"

//Flag
#define DRAW_DEBUGHELPER			//Draw Debug On/Off

//컨트롤 종류
enum class ControlMode
{
	PLAYER,
	NPC
};

//시점 종류
enum class ViewMode
{
	TESTVIEW,
	COMMONVIEW,
	ZOOMIN
};

//PlayerState
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	PREINIT,	//캐릭터 생성전의 스테이트, 캐릭터와 UI를 숨긴다.
	LOADING,	//선택한 캐릭터 애셋을 로딩, 로딩이 완료될때까지 입력을 비활성화
	READY,		//애셋 로딩 완료, 캐릭터와 UI를 볼수있고, 입력을 활성화
	DEAD		//UI 종료, 컨트롤 비활성화, Collision off
};