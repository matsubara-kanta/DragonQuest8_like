// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle_Command_Widget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"



UBattle_Command_Widget::UBattle_Command_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), kougeki_button(nullptr)
{
	static ConstructorHelpers::FObjectFinder< USoundBase > find_sound(TEXT("/Script/Engine.SoundWave'/Game/DragonQuest8_like/Scenes/Battle/Select_SE.Select_SE'"));
	if (find_sound.Succeeded()) {
		Sound_Select = find_sound.Object;
	}

}

void UBattle_Command_Widget::NativeConstruct() {
	Super::NativeConstruct();
	//UE_LOG(LogTemp, Warning, TEXT("Output3: %s"), *HBox_Child->GetAllChildren()[i]->GetName());

	for (int32 index = 0; index < ENEMY_NUM_MAX; ++index) {
		FString str1 = "Enemy_Text" + FString::FromInt(index + 1);
		UTextBlock* tmp = Cast<UTextBlock>(GetWidgetFromName(FName(str1)));
		ensure(tmp != nullptr);
		if (tmp != nullptr)
		{
			enemy_texts.Add(tmp);
		}

		FString str2 = "Enemy_Button" + FString::FromInt(index + 1);
		UButton* button = Cast<UButton>(GetWidgetFromName(FName(str2)));
		ensure(button != nullptr);
		if (button != nullptr)
		{
			enemy_buttons.Add(button);
		}

		FString str3 = "Enemy_Num_Text" + FString::FromInt(index + 1);
		UTextBlock* text = Cast<UTextBlock>(GetWidgetFromName(FName(str3)));
		ensure(text != nullptr);
		if (text != nullptr)
		{
			enemy_num_texts.Add(text);
		}

	}

	Enemy_Infos_Init();
	Create_Enemy_UI();

	UCanvasPanel* panel1 = Cast<UCanvasPanel>(GetWidgetFromName("Enemy_Panel"));
	ensure(panel1 != nullptr);
	if (panel1 != nullptr) {
		enemy_canvas = panel1;
	}


	UButton* Button = Cast<UButton>(GetWidgetFromName("Kougeki_Button"));
	ensure(Button != nullptr);
	if (Button != nullptr) {
		kougeki_button = Button;
	}

	if (!kougeki_button->OnClicked.IsBound()) {
		kougeki_button->OnClicked.AddDynamic(this, &UBattle_Command_Widget::Pressed_kougeki);
	}

	USpacer* spacer = Cast<USpacer>(GetWidgetFromName("Disable_Spacer"));
	ensure(spacer != nullptr);
	if (spacer != nullptr) {
		disable_spacer = spacer;
	}

	UCanvasPanel* panel2 = Cast<UCanvasPanel>(GetWidgetFromName("Party_Panel"));
	ensure(panel2 != nullptr);
	if (panel2 != nullptr) {
		party_canvas = panel2;
	}


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

void UBattle_Command_Widget::Create_Enemy_UI()
{

	enemy_num = FMath::RandRange(1, ENEMY_NUM_MAX);

	for (int32 Index = 0; Index < enemy_num; ++Index)
	{
		if (enemy_texts[Index] != nullptr)
		{
			FSlateColor Color = FLinearColor::White;
			enemy_texts[Index]->SetColorAndOpacity(Color);
			FSlateFontInfo TextInfo = enemy_texts[Index]->GetFont();
			TextInfo.Size = FONT_SIZE;
			enemy_texts[Index]->SetFont(TextInfo);
			enemy_texts[Index]->SetText(FText::FromString(Enemy_Infos[Index].Name));
		}

	}
}

void UBattle_Command_Widget::Enemy_Infos_Init()
{
	Enemy_Infos = { {10,10,10,10,10,10,10,1,"Corpse_Melee",true},
{20,20,20,20,20,20,20,2,"Corpse_Sword",true},{30,30,30,30,30,30,30,3,"Large_Sword3",true},{10,10,10,10,10,10,10,4,"Charger",true} };
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