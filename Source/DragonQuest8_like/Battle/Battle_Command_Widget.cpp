// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Command_Widget.h"
#include "GameFramework/Character.h"
#include "../EnemyCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Battle_State.h"



UBattle_Command_Widget::UBattle_Command_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), kougeki_button(nullptr)
{
}

void UBattle_Command_Widget::NativeConstruct() {
	Super::NativeConstruct();
	//UE_LOG(LogTemp, Warning, TEXT("Output3: %s"), *HBox_Child->GetAllChildren()[i]->GetName());
}


void UBattle_Command_Widget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBattle_Command_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBattle_Command_Widget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBattle_Command_Widget::NativePreConstruct()
{
	Super::NativePreConstruct();
}



void UBattle_Command_Widget::Create_Enemy_UI(TArray<AEnemyCharacter*> enemy_actors)
{
	if (enemy_texts.Num() != 0)
	{
		for (int32 index = 0; index < enemy_actors.Num(); ++index)
		{
			FSlateColor Color = FLinearColor::White;
			enemy_texts[index]->SetColorAndOpacity(Color);
			FSlateFontInfo TextInfo = enemy_texts[index]->GetFont();
			TextInfo.Size = FONT_SIZE;
			enemy_texts[index]->SetFont(TextInfo);
			//UKismetSystemLibrary::PrintString(this, "enemy: " + enemy_actors[index]->getRecord().NAME.ToString());
			enemy_texts[index]->SetText(enemy_actors[index]->getRecord().NAME);
		}

	}
}


void UBattle_Command_Widget::Pressed_kougeki()
{
	UGameplayStatics::PlaySound2D(GetWorld(), Sound_Select);
	enemy_canvas->SetVisibility(ESlateVisibility::Visible);
	for (int32 index = 0; index < enemy_num; ++index)
	{
		enemy_buttons[index]->SetVisibility(ESlateVisibility::Visible);
		enemy_texts[index]->SetVisibility(ESlateVisibility::Visible);
		enemy_num_texts[index]->SetVisibility(ESlateVisibility::Visible);
	}

	disable_spacer->SetVisibility(ESlateVisibility::Visible);
	setkougekiButton(false);
	party_canvas->SetRenderOpacity(0.4f);
}

bool UBattle_Command_Widget::is_Spacer_Visible()
{
	if (disable_spacer->GetVisibility() == ESlateVisibility::Visible)
		return true;
	else
		return false;
}

void UBattle_Command_Widget::backCommand()
{
	disable_spacer->SetVisibility(ESlateVisibility::Hidden);
	enemy_canvas->SetVisibility(ESlateVisibility::Hidden);
	party_canvas->SetRenderOpacity(1.0f);
}


void UBattle_Command_Widget::setkougekiButton(bool b)
{
	kougeki_button->SetIsEnabled(b);
}

void UBattle_Command_Widget::Dec_EnemyArray()
{
	/* 配列の末尾の要素を削除して、決定したコマンドをリセット */
	if (!enemy_array.IsEmpty())
		enemy_array.RemoveAt(enemy_array.Num() - 1);
}

void UBattle_Command_Widget::Enemy_Button_Clicked(UButton* button)
{
	if (enemy_array.Num() < player_num) {
		int32 index = *enemy_buttons.FindKey(button);
		enemy_array.Add(index);
		state = Battle_State::Disable;
		backCommand();
		setkougekiButton(true);
	}
}
TArray<int32> UBattle_Command_Widget::getArray()
{
	return enemy_array;
}

void UBattle_Command_Widget::setEnemy_Num(int32 num)
{
	enemy_num = num;
}

void UBattle_Command_Widget::Command_Wait(TArray<ADragonQuest8_likeCharacter*> player)
{
	if (enemy_array.Num() < player_num)
		character_name->SetText(player[enemy_array.Num()]->getRecord().NAME);

	if (player_num == enemy_array.Num() && state != Battle_State::Attack)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		state = Battle_State::Attack;
		UKismetSystemLibrary::PrintString(this, "Attack");
	}

}

void UBattle_Command_Widget::Init(int32 num, TSet<int32> set)
{
	enemy_array.Empty();
	setPlayerNum(num);
	this->SetVisibility(ESlateVisibility::Visible);

	/* 倒した敵キャラを対象から除外するため、ボタンを削除 */
	for (int32 id : set)
	{
		enemy_buttons[id]->RemoveFromParent();
		enemy_num_texts[id]->RemoveFromParent();
	}

}

void UBattle_Command_Widget::Enable()
{
}

void UBattle_Command_Widget::Disable()
{
	state = Battle_State::Enable;
}

void UBattle_Command_Widget::setPlayerNum(int32 num)
{
	player_num = num;
}