// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle_First_Widget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../PlayerDataAsset.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../DQ8GameInstance.h"
#include "Battle_State.h"


UBattle_First_Widget::UBattle_First_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), Battle_Switcher(nullptr)
{

}

void UBattle_First_Widget::NativeConstruct() 
{
	Super::NativeConstruct();
}

// Tickèàóù
void UBattle_First_Widget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// åpè≥å≥èàóù
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UBattle_First_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBattle_First_Widget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBattle_First_Widget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBattle_First_Widget::Init_Player(TMap<int32,FPlayerDataAssetRecord> player_infos)
{
	//UKismetSystemLibrary::PrintString(this, FString::FromInt(player_infos.Num()), true, true, FColor::Cyan, 50.f, TEXT("None"));
	//UE_LOG(LogTemp, Warning, TEXT("num: %d"), player_infos.Num());

	for (int32 index = 0; index != player_infos.Num(); ++index)
	{
		int32 HP = player_infos.Find(index)->HP;
		int32 MP = player_infos.Find(index)->MP;
		int32 Lv = player_infos.Find(index)->Lv;
		FString Str_HP = FString::Printf(TEXT("HP : %d"), HP);
		FString Str_MP = FString::Printf(TEXT("MP : %d"), MP);
		FString Str_Lv = FString::Printf(TEXT("Lv   : %d"), Lv);
		Texts[index].HP_Text->SetText(FText::FromString(Str_HP));
		Texts[index].MP_Text->SetText(FText::FromString(Str_MP));
		Texts[index].Lv_Text->SetText(FText::FromString(Str_Lv));
	}

}

void UBattle_First_Widget::Update(TMap<int32,FPlayerDataAssetRecord> player_infos)
{
	for (int32 index = 0; index < player_infos.Num(); index++)
	{
		int32 HP = player_infos.Find(index)->HP;
		int32 MP = player_infos.Find(index)->MP;
		FString Str_HP = FString::Printf(TEXT("HP : %d"), HP);
		FString Str_MP = FString::Printf(TEXT("MP : %d"), MP);
		Texts[index].HP_Text->SetText(FText::FromString(Str_HP));
		Texts[index].MP_Text->SetText(FText::FromString(Str_MP));
	}

}

void UBattle_First_Widget::TatakauButton_Clicked()
{
	UGameplayStatics::PlaySound2D(GetWorld(), Sound_Select);
	int32 index = Battle_Switcher->GetActiveWidgetIndex();
	//UE_LOG(LogTemp, Warning, TEXT("index: %d,%d"),index,Battle_Switcher->GetNumWidgets());
	Battle_Switcher->SetActiveWidgetIndex(index + 1);
}

UWidgetSwitcher* UBattle_First_Widget::getSwitcher()
{
	return Battle_Switcher;
}

void UBattle_First_Widget::Change_State()
{
	this->SetIsEnabled(false);
	state = Battle_State::Escape;
	bool flag; // ì¶Ç∞ÇÁÇÍÇÈÇ©Ç«Ç§Ç©
	int random = FMath::RandRange(0, 9);
	if (random % 3 != 0) {
		flag = true;
	}
	else
	{
		flag = false;
	}

	UGameplayStatics::PlaySound2D(GetWorld(), Sound_Select);

	if (flag) {
		FLatentActionInfo LatentInfo;
		//UGameplayStatics::LoadStreamLevel(GetWorld(), "Field", false, false, LatentInfo);
		UGameplayStatics::PlaySound2D(GetWorld(), Sound_Nigeru);
		TFunction<void(void)> Func = [this]() {
			UGameplayStatics::OpenLevel(GetWorld(), "Field", true);
		};
		FTimerHandle Handle;
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		GetWorld()->GetTimerManager().SetTimer(Handle, (TFunction<void(void)>&&)Func, 3.0f, false);
	}
	else {
		state = Battle_State::Init;
	}
}

void UBattle_First_Widget::Command_Wait()
{
}

void UBattle_First_Widget::Attack()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UBattle_First_Widget::Escape()
{

}

void UBattle_First_Widget::Init()
{
	this->SetVisibility(ESlateVisibility::Visible);
	this->SetIsEnabled(true);
	Battle_Switcher->SetActiveWidgetIndex(0);
}