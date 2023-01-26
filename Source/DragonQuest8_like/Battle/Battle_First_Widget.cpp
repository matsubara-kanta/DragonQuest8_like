// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle_First_Widget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../PlayerDataAsset.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../DQ8GameInstance.h"
#include "Battle_State.h"


UBattle_First_Widget::UBattle_First_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), Hero_HP_Text(nullptr), Hero_MP_Text(nullptr), Hero_Lv_Text(nullptr), Yangasu_HP_Text(nullptr),
	Yangasu_MP_Text(nullptr), Yangasu_Lv_Text(nullptr), Tatakau_Button(nullptr), Nigeru_Button(nullptr), Odokasu_Button(nullptr), Sakusen_Button(nullptr), Command_Box(nullptr), Battle_Switcher(nullptr), Sound_Select(nullptr)
{
	static ConstructorHelpers::FObjectFinder< USoundBase > find_sound(TEXT("/Script/Engine.SoundWave'/Game/DragonQuest8_like/Scenes/Battle/Select_SE.Select_SE'"));
	if (find_sound.Succeeded()) {
		Sound_Select = find_sound.Object;
	}

	static ConstructorHelpers::FObjectFinder< USoundBase > find_sound2(TEXT("/Script/Engine.SoundWave'/Game/DragonQuest8_like/Scenes/Battle/Nigeru_SE.Nigeru_SE'"));
	if (find_sound2.Succeeded()) {
		Sound_Nigeru = find_sound2.Object;
	}

}

void UBattle_First_Widget::NativeConstruct() {
	Super::NativeConstruct();

	/* Text èàóù */
	UTextBlock* tmp = Cast<UTextBlock>(GetWidgetFromName("Hero_HP_Text"));
	ensure(tmp != nullptr);
	if (tmp != nullptr) {
		Hero_HP_Text = tmp;
		Hero_Text.Insert(Hero_HP_Text, INDEX_HP);
	}


	tmp = Cast<UTextBlock>(GetWidgetFromName("Hero_MP_Text"));
	ensure(tmp != nullptr);
	if (tmp != nullptr) {
		Hero_MP_Text = tmp;
		Hero_Text.Insert(Hero_MP_Text, INDEX_MP);
	}


	tmp = Cast<UTextBlock>(GetWidgetFromName("Hero_Lv_Text"));
	ensure(tmp != nullptr);
	if (tmp != nullptr) {
		Hero_Lv_Text = tmp;
		Hero_Text.Insert(Hero_Lv_Text, INDEX_Lv);
	}


	tmp = Cast<UTextBlock>(GetWidgetFromName("Yangasu_HP_Text"));
	ensure(tmp != nullptr);
	if (tmp != nullptr) {
		Yangasu_HP_Text = tmp;
		Yangasu_Text.Insert(Yangasu_HP_Text, INDEX_HP);
	}

	tmp = Cast<UTextBlock>(GetWidgetFromName("Yangasu_MP_Text"));
	ensure(tmp != nullptr);
	if (tmp != nullptr) {
		Yangasu_MP_Text = tmp;
		Yangasu_Text.Insert(Yangasu_MP_Text, INDEX_MP);
	}

	tmp = Cast<UTextBlock>(GetWidgetFromName("Yangasu_Lv_Text"));
	ensure(tmp != nullptr);
	if (tmp != nullptr) {
		Yangasu_Lv_Text = tmp;
		Yangasu_Text.Insert(Yangasu_Lv_Text, INDEX_Lv);
	}

	/* É{É^Éìèàóù */

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
		Nigeru_Button->OnClicked.AddDynamic(this, &UBattle_First_Widget::Change_State);
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

	UWidgetSwitcher* Switcher = Cast<UWidgetSwitcher>(GetWidgetFromName("Battle_Switcher"));
	ensure(Switcher != nullptr);
	if (Switcher != nullptr) {
		Battle_Switcher = Switcher;
	}


	Text.Add(Hero_Text);
	Text.Add(Yangasu_Text);
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

void UBattle_First_Widget::Init(TArray<FPlayerDataAssetRecord> player_infos)
{
	//UKismetSystemLibrary::PrintString(this, FString::FromInt(player_infos.Num()), true, true, FColor::Cyan, 50.f, TEXT("None"));
	//UE_LOG(LogTemp, Warning, TEXT("num: %d"), player_infos.Num());

	for (int32 Index = 0; Index != player_infos.Num(); ++Index)
	{
		int32 HP = player_infos[Index].HP;
		int32 MP = player_infos[Index].MP;
		int32 Lv = player_infos[Index].Lv;
		FString Str_HP = FString::Printf(TEXT("HP : %d"), HP);
		FString Str_MP = FString::Printf(TEXT("MP : %d"), MP);
		FString Str_Lv = FString::Printf(TEXT("Lv   : %d"), Lv);
		Text[Index][INDEX_HP]->SetText(FText::FromString(Str_HP));
		Text[Index][INDEX_MP]->SetText(FText::FromString(Str_MP));
		Text[Index][INDEX_Lv]->SetText(FText::FromString(Str_Lv));
	}

}

void UBattle_First_Widget::Update(TArray<FPlayerDataAssetRecord> player_infos)
{
	for (int32 Index = 0; Index < player_infos.Num(); Index++)
	{
		int32 HP = player_infos[Index].HP;
		int32 MP = player_infos[Index].MP;
		FString Str_HP = FString::Printf(TEXT("HP : %d"), HP);
		FString Str_MP = FString::Printf(TEXT("MP : %d"), MP);
		Text[Index][INDEX_HP]->SetText(FText::FromString(Str_HP));
		Text[Index][INDEX_MP]->SetText(FText::FromString(Str_MP));
	}

}

void UBattle_First_Widget::Invisible_Clicked()
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
	setBattle_First_Widget(false);
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
		state = Battle_State::Command_Wait;
	}
}

void UBattle_First_Widget::setBattle_First_Widget(bool b)
{
	this->SetIsEnabled(b);
}