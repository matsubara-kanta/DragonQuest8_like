// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Engine.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/ButtonSlot.h"
#include "Enemy.h"
#include "Battle_Command_Widget.generated.h"

#define FONT_SIZE 32

/**
 * 
 */
UCLASS()
class UBattle_Command_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBattle_Command_Widget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;

private:
	UVerticalBox* Enemy_VBox;
	void Create_Enemy_UI();
	TArray<FEnemy> Enemy_Infos = { {10,10,10,10,10,10,10,1,"Corpse_Melee",true},
{20,20,20,20,20,20,20,2,"Corpse_Sword"},{30,30,30,30,30,30,30,3,"Large_Sword3",true} };



};
