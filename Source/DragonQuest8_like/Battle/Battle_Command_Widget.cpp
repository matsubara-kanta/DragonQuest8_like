// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Command_Widget.h"
#include "GameFramework/Character.h"
#include "../EnemyCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"



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

			if (!enemy_buttons[index]->OnClicked.IsBound()) {
				enemy_buttons[index]->OnClicked.AddDynamic(this, &UBattle_Command_Widget::Enemy_Button_Clicked);
			}

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

void UBattle_Command_Widget::Enemy_Button_Clicked()
{

}

TArray<TPair<int32, int32>> UBattle_Command_Widget::getPair()
{
	return pair;
}

void UBattle_Command_Widget::setEnemy_Num(int32 num)
{
	enemy_num = num;
}