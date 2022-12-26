// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle_Command_Widget.h"
#include "Blueprint/UserWidget.h"

UBattle_Command_Widget::UBattle_Command_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
void UBattle_Command_Widget::NativeConstruct() {
	Super::NativeConstruct();
}


void UBattle_Command_Widget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
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