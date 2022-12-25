// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Party_Member.h"
#include "BattleWidget.generated.h"

/**
 * 
 */
UCLASS()
class UBattleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UBattleWidget(const FObjectInitializer& ObjectInitializer);
protected :
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
private:
	UTextBlock* Hero_HP_Text;
	UTextBlock* Hero_MP_Text;
	UTextBlock* Hero_Lv_Text;
	UTextBlock* Yangasu_HP_Text;
	UTextBlock* Yangasu_MP_Text;
	UTextBlock* Yangasu_Lv_Text;
	TArray<FParty_Member> Party_Infos = { {15,21,8,10,10,10,10,10,"エイト"},
	{20,5,9,20,20,20,20,20,"ヤンガス"} };
	bool flag;
};
