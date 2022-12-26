// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Party_Member.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Engine.h"
#include "Components/Border.h"
#include "Battle_Command_Widget.h"
#include <Components/WidgetSwitcher.h>
#include "Battle_First_Widget.generated.h"


UCLASS()
class UBattle_First_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UBattle_First_Widget(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
	UFUNCTION(BlueprintCallable, Category = "Test")
		void TestClicked() { UE_LOG(LogTemp, Log, TEXT("Clicked")); }
	UFUNCTION(BlueprintCallable, Category = "Property")
		void Invisible_Clicked();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> WBP_Battle_Command;

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
	UBattle_Command_Widget* Battle_Command_w;
	UWidgetSwitcher* Battle_Switcher;


	TArray<FParty_Member> Party_Infos = { {15,21,8,10,10,10,10,10,"エイト"},
	{20,5,9,20,20,20,20,20,"ヤンガス"} };
};
