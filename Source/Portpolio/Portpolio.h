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