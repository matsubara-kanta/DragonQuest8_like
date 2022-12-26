// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle_First_Widget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"

UBattle_First_Widget::UBattle_First_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), Hero_HP_Text(nullptr), Hero_MP_Text(nullptr), Hero_Lv_Text(nullptr), Yangasu_HP_Text(nullptr),
	Yangasu_MP_Text(nullptr), Yangasu_Lv_Text(nullptr), Tatakau_Button(nullptr), Nigeru_Button(nullptr), Odokasu_Button(nullptr), Sakusen_Button(nullptr), Command_Box(nullptr), Command_Border(nullptr), Battle_Switcher(nullptr)
{
}

void UBattle_First_Widget::NativeConstruct() {
	Super::NativeConstruct();

	/* Text 処理 */
	UTextBlock* tmp = Cast<UTextBlock>(GetWidgetFromName("Hero_HP_Text"));
	ensure(tmp != nullptr);
	if (tmp != nullptr) {
		Hero_HP_Text = tmp;
	}


	tmp = Cast<UTextBlock>(GetWidgetFromName("Hero_MP_Text"));
	ensure(tmp != nullptr);
	if (tmp != nullptr) {
		Hero_MP_Text = tmp;
	}


	tmp = Cast<UTextBlock>(GetWidgetFromName("Hero_Lv_Text"));
	ensure(tmp != nullptr);
	if (tmp != nullptr) {
		Hero_Lv_Text = tmp;
	}
	int32 Hero_Lv = Party_Infos[0].Lv;
	FString Str_Lv_H = FString::Printf(TEXT("Lv   : %d"), Hero_Lv);
	Hero_Lv_Text->SetText(FText::FromString(Str_Lv_H));

	tmp = Cast<UTextBlock>(GetWidgetFromName("Yangasu_HP_Text"));
	ensure(tmp != nullptr);
	if (tmp != nullptr) {
		Yangasu_HP_Text = tmp;
	}

	tmp = Cast<UTextBlock>(GetWidgetFromName("Yangasu_MP_Text"));
	ensure(tmp != nullptr);
	if (tmp != nullptr) {
		Yangasu_MP_Text = tmp;
	}

	tmp = Cast<UTextBlock>(GetWidgetFromName("Yangasu_Lv_Text"));
	ensure(tmp != nullptr);
	int32 Yangasu_Lv = Party_Infos[1].Lv;
	if (tmp != nullptr) {
		Yangasu_Lv_Text = tmp;
	}
	FString Str_Lv = FString::Printf(TEXT("Lv   : %d"), Yangasu_Lv);
	Yangasu_Lv_Text->SetText(FText::FromString(Str_Lv));

	/* ボタン処理 */

	UButton* Button = Cast<UButton>(GetWidgetFromName("Tatakau_Button"));
	ensure(Button != nullptr);
	if (Button != nullptr) {
		Tatakau_Button = Button;
	}
	if (!Tatakau_Button->OnClicked.IsBound()) {
		Tatakau_Button->OnClicked.AddDynamic(this, &UBattle_First_Widget::Invisible_Clicked);
	}

	Button = Cast<UButton>(GetWidgetFromName("Nigeru_Button"));
	ensure(Button != nullptr);
	if (Button != nullptr) {
		Nigeru_Button = Button;
	}
	if (!Nigeru_Button->OnClicked.IsBound()) {
		Nigeru_Button->OnClicked.AddDynamic(this, &UBattle_First_Widget::Invisible_Clicked);
	}

	Button = Cast<UButton>(GetWidgetFromName("Odokasu_Button"));
	ensure(Button != nullptr);
	if (Button != nullptr) {
		Odokasu_Button = Button;
	}
	if (!Odokasu_Button->OnClicked.IsBound()) {
		Odokasu_Button->OnClicked.AddDynamic(this, &UBattle_First_Widget::Invisible_Clicked);
	}

	Button = Cast<UButton>(GetWidgetFromName("Sakusen_Button"));
	ensure(Button != nullptr);
	if (Button != nullptr) {
		Sakusen_Button = Button;
	}
	if (!Sakusen_Button->OnClicked.IsBound()) {
		Sakusen_Button->OnClicked.AddDynamic(this, &UBattle_First_Widget::Invisible_Clicked);
	}

	UVerticalBox* Box = Cast<UVerticalBox>(GetWidgetFromName("Command_Box"));
	ensure(Box != nullptr);
	if (Box != nullptr) {
		Command_Box = Box;
	}

	UBorder* Border = Cast<UBorder>(GetWidgetFromName("Command_Border"));
	ensure(Border != nullptr);
	if (Border != nullptr) {
		Command_Border = Border;
	}

	UWidgetSwitcher* Switcher = Cast<UWidgetSwitcher>(GetWidgetFromName("Battle_Switcher"));
	ensure(Switcher != nullptr);
	if (Switcher != nullptr) {
		Battle_Switcher = Switcher;
	}


}

// Tick処理
void UBattle_First_Widget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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

void UBattle_First_Widget::Invisible_Clicked()
{
	Command_Box->SetVisibility(ESlateVisibility::Collapsed);
	Command_Border->SetVisibility(ESlateVisibility::Collapsed);
	int32 index = Battle_Switcher->GetActiveWidgetIndex();
	UE_LOG(LogTemp, Warning, TEXT("index: %d,%d"),index,Battle_Switcher->GetNumWidgets());
	Battle_Switcher->SetActiveWidgetIndex(index + 1);
}