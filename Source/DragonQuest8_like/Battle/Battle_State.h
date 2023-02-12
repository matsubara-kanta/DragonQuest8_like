// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class Battle_State
{
	Command_Wait, // ���͑҂�
	Attack, // �U��
	Escape, // ������
	Finish, // �퓬�I��
	Disable, // ���͖���
	Enable, // ���͎�t
	Init, // ������
	Nop, // �������Ȃ�
};

extern Battle_State state;
