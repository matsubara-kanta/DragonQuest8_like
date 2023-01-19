// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class Battle_State
{
	Command_Wait,
	Attack,
	Escape,
};

extern Battle_State state;
