// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Engine.h"
#include "Components/Border.h"
#include "Battle_Command_Widget.h"
#include "Components/WidgetSwitcher.h"
#include "BattleCharacter.h"
#include "Battle_First_Widget.generated.h"

#define INDEX_HP 0
#define INDEX_MP 1
#define INDEX_Lv 2

UCLASS()
class UBattle_First_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UBattle_First_Widget(const FObjectInitializer& ObjectInitializer);
	UWidgetSwitcher* getSwitcher();
	void Init(TArray<BattleCharacter*> Party_Infos);
	void Update(TArray<BattleCharacter*> Party_Infos);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
	UFUNCTION(BlueprintCallable, Category = "Test")
		void TestClicked() { UE_LOG(LogTemp, Log, TEXT("Clicked")); }
	UFUNCTION(BlueprintCallable, Category = "Myfunc")
		void Invisible_Clicked();
	UFUNCTION(BlueprintCallable, Category = "Myfunc")
		void Change_State();

private:
	UTextBlock* Hero_HP_Text;
	UTextBlock* Hero_MP_Text;
	UTextBlock* Hero_Lv_Text;
	UTextBlock* Yangasu_HP_Text;
	UTextBlock* Yangasu_MP_Text;
	UTextBlock* Yangasu_Lv_Text;
	UButton* Tatakau_Button;
	UButton* Nigeru_Button;
	UButton* Odokasu_Button;
	UButton* Sakusen_Button;
	UVerticalBox* Command_Box;
	UCanvas* Command_Canvas;
	UBorder* Command_Border;
	UWidgetSwitcher* Battle_Switcher;
	USoundBase* Sound_Select;
	USoundBase* Sound_Nigeru;
	TArray<UTextBlock*> Hero_Text;
	TArray<UTextBlock*> Yangasu_Text;
	TArray<TArray<UTextBlock*>> Text;


};
