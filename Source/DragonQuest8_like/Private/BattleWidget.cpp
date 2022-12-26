// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleWidget.h"
#include "Blueprint/UserWidget.h"

UBattleWidget::UBattleWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), Hero_HP_Text(nullptr), Hero_MP_Text(nullptr), Hero_Lv_Text(nullptr), Yangasu_HP_Text(nullptr),
	Yangasu_MP_Text(nullptr), Yangasu_Lv_Text(nullptr)
{
}

void UBattleWidget::NativeConstruct() {
	Super::NativeConstruct();
}

// Tick処理
void UBattleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// 継承元処理
	Super::NativeTick(MyGeometry, InDeltaTime);

	// テキスト書き換え
	if (Hero_HP_Text && Hero_MP_Text && Hero_Lv_Text) {
		int32 Hero_HP = Party_Infos[0].HP;
		int32 Hero_MP = Party_Infos[0].MP;

		FString Str_HP = FString::Printf(TEXT("HP : %d"), Hero_HP);
		FString Str_MP = FString::Printf(TEXT("MP : %d"), Hero_MP);
		Hero_HP_Text->SetText(FText::FromString(Str_HP));
		Hero_MP_Text->SetText(FText::FromString(Str_MP));


	}

	if (Yangasu_HP_Text && Yangasu_MP_Text && Yangasu_Lv_Text)
	{
		int32 Yangasu_HP = Party_Infos[1].HP;
		int32 Yangasu_MP = Party_Infos[1].MP;
		FString Str_HP = FString::Printf(TEXT("HP : %d"), Yangasu_HP);
		FString Str_MP = FString::Printf(TEXT("MP : %d"), Yangasu_MP);
		Yangasu_HP_Text->SetText(FText::FromString(Str_HP));
		Yangasu_MP_Text->SetText(FText::FromString(Str_MP));

	}

}

void UBattleWidget::NativeOnInitialized(){
	Super::NativeOnInitialized();

	UTextBlock*  tmp = Cast<UTextBlock>(GetWidgetFromName("Hero_HP_Text"));
	ensure(tmp != nullptr);
	Hero_HP_Text = tmp;


	tmp = Cast<UTextBlock>(GetWidgetFromName("Hero_MP_Text"));
	ensure(tmp != nullptr);
	Hero_MP_Text = tmp;


	tmp = Cast<UTextBlock>(GetWidgetFromName("Hero_Lv_Text"));
	ensure(tmp != nullptr);
	Hero_Lv_Text = tmp;
	int32 Hero_Lv = Party_Infos[0].Lv;
	FString Str_Lv_H = FString::Printf(TEXT("Lv   : %d"), Hero_Lv);
	Hero_Lv_Text->SetText(FText::FromString(Str_Lv_H));

	tmp = Cast<UTextBlock>(GetWidgetFromName("Yangasu_HP_Text"));
	ensure(tmp != nullptr);
	Yangasu_HP_Text = tmp;


	tmp = Cast<UTextBlock>(GetWidgetFromName("Yangasu_MP_Text"));
	ensure(tmp != nullptr);
	Yangasu_MP_Text = tmp;


	tmp = Cast<UTextBlock>(GetWidgetFromName("Yangasu_Lv_Text"));
	ensure(tmp != nullptr);
	int32 Yangasu_Lv = Party_Infos[1].Lv;
	Yangasu_Lv_Text = tmp;
	FString Str_Lv = FString::Printf(TEXT("Lv   : %d"), Yangasu_Lv);
	Yangasu_Lv_Text->SetText(FText::FromString(Str_Lv));


}

void UBattleWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBattleWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}
