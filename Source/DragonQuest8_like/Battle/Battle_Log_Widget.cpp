// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle_Log_Widget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

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
	log_text->SetVisibility(ESlateVisibility::Visible);
	log_text->SetText(FText::FromString(str));
}

void UBattle_Log_Widget::Dead_Update(FString str,float time)
{
	log_dead_text->SetVisibility(ESlateVisibility::Visible);
	log_dead_text->SetText(FText::FromString(str));
	TFunction<void(void)> Func = [this]() {
		log_dead_text->SetVisibility(ESlateVisibility::Collapsed);
		log_text->SetVisibility(ESlateVisibility::Collapsed);
	};
	FTimerHandle Handle;
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	GetWorld()->GetTimerManager().SetTimer(Handle, (TFunction<void(void)>&&)Func, 1.5f, false);
}

void UBattle_Log_Widget::Init()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UBattle_Log_Widget::Dead_Finish(FString str)
{
	log_text->SetVisibility(ESlateVisibility::Visible);
	log_dead_text->SetVisibility(ESlateVisibility::Visible);
	log_dead_text->SetText(FText::FromString(str));
}


void UBattle_Log_Widget::Collapsed()
{
	log_dead_text->SetVisibility(ESlateVisibility::Collapsed);
}