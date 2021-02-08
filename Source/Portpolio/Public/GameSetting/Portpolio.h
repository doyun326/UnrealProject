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

//�׸� ����
#define REST_GRIPSOCKET		"RestGripPoint"
#define FIRE_GRIPSOCKET		"FireGripPoint"
#define SPRINT_GRIPSOCKET	"SprintGripPoint"
#define WALK_GRIPSOCKET		"WalkGripPoint"

//Flag
#define DRAW_DEBUGHELPER			//Draw Debug On/Off

//��Ʈ�� ����
enum class ControlMode
{
	PLAYER,
	NPC
};

//���� ����
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
	PREINIT,	//ĳ���� �������� ������Ʈ, ĳ���Ϳ� UI�� �����.
	LOADING,	//������ ĳ���� �ּ��� �ε�, �ε��� �Ϸ�ɶ����� �Է��� ��Ȱ��ȭ
	READY,		//�ּ� �ε� �Ϸ�, ĳ���Ϳ� UI�� �����ְ�, �Է��� Ȱ��ȭ
	DEAD		//UI ����, ��Ʈ�� ��Ȱ��ȭ, Collision off
};