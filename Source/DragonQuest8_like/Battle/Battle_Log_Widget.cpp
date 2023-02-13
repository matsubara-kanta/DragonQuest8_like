// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle_Log_Widget.h"

UBattle_Log_Widget::UBattle_Log_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBattle_Log_Widget::NativeConstruct() {
	Super::NativeConstruct();
	//UE_LOG(LogTemp, Warning, TEXT("Output3: %s"), *HBox_Child->GetAllChildren()[i]->GetName());
}


void UBattle_Log_Widget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBattle_Log_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBattle_Log_Widget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBattle_Log_Widget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBattle_Log_Widget::Update(FString str)
{
	//FString Str_HP = FString::Printf(TEXT("HP : %d"), HP);
	ensure(log_text);
	log_text->SetText(FText::FromString(str));
}
