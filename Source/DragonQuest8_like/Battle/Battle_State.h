// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class Battle_State : uint8
{
	Command_Wait, // 入力待ち
	Attack, // 攻撃
	Escape, // 逃げる
	Finish, // 戦闘終了
	Disable, // 入力無効
	Enable, // 入力受付
	Init, // 初期化
	Animation, // アニメーション中
	AnimationFinished, // アニメーション終わり
	Nop, // 何もしない
	LevelUp, // レベルアップ
	Wait, // 待つ
};

extern Battle_State state;
