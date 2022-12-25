// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.generated.h"



/**
 *
 */
USTRUCT(BlueprintType)

struct FEnemy
{
	GENERATED_BODY()

		int32 HP;
	int32 Attack;
	int32 Defense;
	int32 M_Attack;
	int32 M_Defense;
	int32 Speed;

	FString Name;
};
