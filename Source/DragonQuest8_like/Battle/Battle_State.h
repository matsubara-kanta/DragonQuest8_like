// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class Battle_State
{
	Command_Wait, // 入力待ち
	Attack, // 攻撃
	Escape, // 逃げる
	Finish, // 戦闘終了
	Disable, // 入力無効
	Enable, // 入力受付
	Init, // 初期化
	Nop, // 何もしない
};

extern Battle_State state;
