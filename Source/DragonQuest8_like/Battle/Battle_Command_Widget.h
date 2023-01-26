// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/Spacer.h"
#include "Engine.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/ButtonSlot.h"
#include "Components/CanvasPanel.h"
#include "../DQ8GameInstance.h"
#include "../EnemyCharacter.h"
#include "Battle_Command_Widget.generated.h"

#define ENEMY_NUM_MAX 5
#define FONT_SIZE 32
#define MAX_POS_R 400
#define MAX_POS_L -400


/**
 * 
 */


UCLASS()
class UBattle_Command_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBattle_Command_Widget(const FObjectInitializer& ObjectInitializer);
	bool is_Spacer_Visible();
	void backCommand();
	void setkougekiButton(bool b);
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
	void Create_Enemy_UI(TArray<AEnemyCharacter*> enemy_actors);
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
	void setEnemy_Num(int32 num);
	TArray<TPair<int32, int32>> getPair();





protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;

private:
	UButton* kougeki_button;
	TArray<UButton*> enemy_buttons;
	TArray<UTextBlock*> enemy_texts;
	TArray<UTextBlock*> enemy_num_texts;
	UCanvasPanel* enemy_canvas;
	UCanvasPanel* party_canvas;
	USoundBase* Sound_Select;
	USpacer* disable_spacer;
	TArray<TPair<int32, int32>> pair; // (攻撃プレイヤーのインデックス、攻撃対象のインデックス)
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void Pressed_kougeki();
		UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void Enemy_Button_Clicked();
	int32 enemy_num;



};
