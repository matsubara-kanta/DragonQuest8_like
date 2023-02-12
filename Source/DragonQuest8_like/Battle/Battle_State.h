// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class Battle_State
{
	Command_Wait, // “ü—Í‘Ò‚¿
	Attack, // UŒ‚
	Escape, // “¦‚°‚é
	Finish, // í“¬I—¹
	Disable, // “ü—Í–³Œø
	Enable, // “ü—Íó•t
	Init, // ‰Šú‰»
	Nop, // ‰½‚à‚µ‚È‚¢
};

extern Battle_State state;
