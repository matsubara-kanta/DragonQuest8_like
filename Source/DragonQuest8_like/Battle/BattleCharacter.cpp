// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleCharacter.h"

BattleCharacter::BattleCharacter(int32 hp, int32 mp, int32 lv, int32 atk, int32 def, int32 intl, int32 spd, int32 state, int32 id, FString name)
{
	this->HP = hp;
	this->MP = mp;
	this->Lv = lv;
	this->ATK = atk;
	this->DEF = def;
	this->INT = intl;
	this->SPD = spd;
	this->STATE = state;
	this->ID = id;
	this->NAME = name;
}

BattleCharacter::~BattleCharacter()
{
}

void BattleCharacter::Attack()
{

}


void BattleCharacter::setHP(int32 hp)
{
	this->HP = hp;
}

void BattleCharacter::setMP(int32 mp)
{
	this->MP = mp;
}

void BattleCharacter::setLv(int32 lv)
{
	this->Lv = lv;
}

void BattleCharacter::setATK(int32 atk)
{
	this->ATK = atk;
}

void BattleCharacter::setDEF(int32 def)
{
	this->DEF = def;
}

void BattleCharacter::setINT(int32 intl)
{
	this->INT = intl;
}

void BattleCharacter::setSPD(int32 spd)
{
	this->SPD = spd;
}

void BattleCharacter::setState(int32 state)
{
	this->STATE = state;
}

void BattleCharacter::setID(int32 id)
{
	this->ID = id;
}

void BattleCharacter::setName(FString name)
{
	this->NAME = name;
}


int32 BattleCharacter::getHP()
{
	return HP;
}

int32 BattleCharacter::getMP()
{
	return MP;
}

int32 BattleCharacter::getLv()
{
	return Lv;
}

int32 BattleCharacter::getATK()
{
	return ATK;
}

int32 BattleCharacter::getDEF()
{
	return DEF;
}

int32 BattleCharacter::getINT()
{
	return INT;
}

int32 BattleCharacter::getSPD()
{
	return SPD;
}

int32 BattleCharacter::getState()
{
	return STATE;
}

int32 BattleCharacter::getID()
{
	return ID;
}

FString BattleCharacter::getName()
{
	return NAME;
}

FString BattleCharacter::printAll()
{
	return "HP:	 " + FString::FromInt(HP) + "            MP:  " + FString::FromInt(MP) + "            Lv:  " + FString::FromInt(Lv) + "           ATK:  " + FString::FromInt(ATK) + "         DEF:  " + FString::FromInt(DEF) + "           INT:  " + FString::FromInt(INT) + "         SPD:  " + FString::FromInt(SPD) + "         STATE:  " + FString::FromInt(STATE) + "           ID:  " + FString::FromInt(ID) + "          NAME:  " + NAME;
}