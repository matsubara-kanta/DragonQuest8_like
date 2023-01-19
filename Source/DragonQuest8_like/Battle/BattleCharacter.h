// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


/**
 *
 */
class  BattleCharacter
{
public:
	BattleCharacter(int32 hp, int32 mp, int32 lv, int32 atk, int32 def, int32 intl , int32 spd, int32 state, int32 id, FString name);
	~BattleCharacter();
	void setHP(int32 hp);
	int32 getHP();
	void setMP(int32 mp);
	int32 getMP();
	void setLv(int32 lv);
	int32 getLv();
	void setATK(int32 atk);
	int32 getATK();
	void setDEF(int32 def);
	int32 getDEF();
	void setINT(int32 intl);
	int32 getINT();
	void setSPD(int32 spd);
	int32 getSPD();
	void setState(int32 state);
	int getState();
	void setID(int32 id);
	int32 getID();
	void setName(FString name);
	FString getName();
	enum Chara_State
	{
		ALIVE,
		DEAD,
	};

	// デバッグ用
	FString printAll();

private:
	int32 HP;
	int32 MP;
	int32 Lv;
	int32 ATK;
	int32 DEF;
	int32 INT;
	int32 SPD;
	int32 STATE; // キャラの状態
	int32 ID;
	FString NAME;

	void Attack();

};
