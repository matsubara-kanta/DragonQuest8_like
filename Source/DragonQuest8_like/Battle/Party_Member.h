// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Party_Member.generated.h"

USTRUCT(BlueprintType)

struct FParty_Member
{
	GENERATED_BODY()

	int32 HP;
	int32 MP;
	int32 Lv;
	int32 Attack;
	int32 Defense;
	int32 M_Attack;
	int32 M_Defense;
	int32 Speed;
	int32 ID;
	FString Name;
	bool alive;
};

extern TArray<FParty_Member> Party_Infos;

