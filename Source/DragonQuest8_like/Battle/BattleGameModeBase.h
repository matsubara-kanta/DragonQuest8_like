// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Battle_First_Widget.h"
#include "Battle_State.h"
#include "BattleCharacter.h"
#include "Components/Spacer.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Battle_Command_Widget.h"
#include "BattleGameModeBase.generated.h"


#define DURATION 2.0f

/**
 *
 */
UCLASS()
class ABattleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABattleGameModeBase();
	~ABattleGameModeBase();
	virtual void Tick(float DeltaTime) override;

protected:
	UBattle_First_Widget* Battle_First_w;
	UBattle_Command_Widget* battle_command_w;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetupInput();
	void PressedB();
	void PressedD();
	void Command_Wait();
	void Attack();
	void Escape();
	TArray<BattleCharacter*> Party_Infos;
	UWidgetSwitcher* switcher;
};
