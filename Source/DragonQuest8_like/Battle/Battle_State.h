// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class Battle_State : uint8
{
	Command_Wait, // ���͑҂�
	Attack, // �U��
	Escape, // ������
	Finish, // �퓬�I��
	Disable, // ���͖���
	Enable, // ���͎�t
	Init, // ������
	Animation, // �A�j���[�V������
	AnimationFinished, // �A�j���[�V�����I���
	Nop, // �������Ȃ�
	LevelUp, // ���x���A�b�v
	Wait, // �҂�
};

extern Battle_State state;
