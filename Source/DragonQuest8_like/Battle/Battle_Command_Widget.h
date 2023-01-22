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
#include "../Field/EnemyDataAsset.h"
#include "../DQ8GameInstance.h"
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
	void decrease_enemy_hp(int32 hp);
	void setkougekiButton(bool b);


protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
	UFUNCTION(BlueprintCallable, Category = "Myfunc")
		void Pressed_kougeki();

private:
	void Create_Enemy_UI();
	void Enemy_Infos_Init();
	void SpawnEnemy();
	void Load_Enemy();
	UButton* kougeki_button;
	TArray<FEnemyDataAssetRecord> Enemy_Infos;
	TArray<UButton*> enemy_buttons;
	TArray<UTextBlock*> enemy_texts;
	TArray<UTextBlock*> enemy_num_texts;
	UCanvasPanel* enemy_canvas;
	UCanvasPanel* party_canvas;
	USoundBase* Sound_Select;
	USpacer* disable_spacer;
	int32 enemy_num;
	UPROPERTY()
		TSoftObjectPtr<class UEnemyDataAsset> enemy_asset;

};
