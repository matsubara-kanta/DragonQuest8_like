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
#include "../DragonQuest8_likeCharacter.h"
#include "Battle_Command_Widget.generated.h"

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
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void Create_Enemy_UI(TArray<AEnemyCharacter*> enemy_actors);
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void setEnemy_Num(int32 num);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* Sound_Select;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCanvasPanel* enemy_canvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCanvasPanel* party_canvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpacer* disable_spacer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UButton* kougeki_button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<int32, UTextBlock*> enemy_texts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<int32, UButton*> enemy_buttons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<int32, UTextBlock*> enemy_num_texts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* character_name;

	void Command_Wait(TArray<ADragonQuest8_likeCharacter*> player);
	void Init(int32 num, TSet<int32> array);
	void Enable();
	void Disable();
	void Dec_EnemyArray();




	UBattle_Command_Widget(const FObjectInitializer& ObjectInitializer);
	bool is_Spacer_Visible();
	void backCommand();
	void setkougekiButton(bool b);
	TArray<int32> getArray();
	void setPlayerNum(int32 num); // 生きているプレイヤーの数





protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void Pressed_kougeki();
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void Enemy_Button_Clicked(UButton* button);

	TArray<int32> enemy_array; // (攻撃プレイヤーのインデックス、攻撃対象のインデックス)
	int32 enemy_num;
	int32 player_num;
	bool flag; // バトルログ遅延制御用



};
