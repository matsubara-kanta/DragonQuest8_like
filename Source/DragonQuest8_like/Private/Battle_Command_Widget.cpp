// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle_Command_Widget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"



UBattle_Command_Widget::UBattle_Command_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBattle_Command_Widget::NativeConstruct() {
	Super::NativeConstruct();
	//UE_LOG(LogTemp, Warning, TEXT("Output3: %s"), *HBox_Child->GetAllChildren()[i]->GetName());


	UVerticalBox* Box = Cast<UVerticalBox>(GetWidgetFromName("Enemy_VBox"));
	ensure(Box != nullptr);
	if (Box != nullptr)
	{
		Enemy_VBox = Box;
	}


	Create_Enemy_UI();

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
	for (int32 Index = 0; Index < Enemy_Infos.Num(); ++Index)
	{
		UHorizontalBox* HBox = NewObject<UHorizontalBox>(UHorizontalBox::StaticClass());
		ensure(HBox != nullptr);

		UTextBlock* Text = NewObject<UTextBlock>(UTextBlock::StaticClass());
		ensure(Text != nullptr);
		if (Text != nullptr)
		{
			FSlateColor Color = FLinearColor::White;
			Text->SetColorAndOpacity(Color);
			FSlateFontInfo TextInfo = Text->GetFont();
			TextInfo.Size = FONT_SIZE;
			Text->SetFont(TextInfo);
			Text->SetText(FText::FromString(Enemy_Infos[Index].Name));
		}

		UTextBlock* Text3 = NewObject<UTextBlock>(UTextBlock::StaticClass());
		ensure(Text3 != nullptr);
		if (Text3 != nullptr)
		{
			FSlateColor Color = FLinearColor::White;
			Text3->SetColorAndOpacity(Color);
			FSlateFontInfo TextInfo = Text3->GetFont();
			TextInfo.Size = FONT_SIZE;
			Text3->SetFont(TextInfo);
			Text3->SetText(FText::FromString("1hiki"));
		}


		UButton* Button = NewObject<UButton>(UButton::StaticClass());
		ensure(Button != nullptr);
		if (Button != nullptr)
		{
			Button->AddChild(Text);
			Button->IsFocusable = true;
			Button->BackgroundColor.A = 0;
			HBox->AddChild(Button);
			HBox->AddChild(Text3);
			Enemy_VBox->AddChild(HBox);

			UVerticalBoxSlot* MySlot = Cast<UVerticalBoxSlot>(Enemy_VBox->GetSlots()[Index+1]);
			ensure(MySlot != nullptr);
			if (MySlot != nullptr)
			{
				MySlot->SetPadding(FMargin(10.0, 10.0, 10.0, 10.0));
				MySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
				MySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			}

			UHorizontalBox* HBox_Child = Cast<UHorizontalBox>(Enemy_VBox->GetAllChildren()[Index+1]);
			ensure(HBox_Child != nullptr);
			if (HBox_Child != nullptr)
			{

				UHorizontalBoxSlot* slot = Cast<UHorizontalBoxSlot>(HBox_Child->GetSlots()[0]);
				ensure(slot != nullptr);
				if (slot != nullptr)
				{
					slot->SetPadding(FMargin(18, 0, 0, 0));
					slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
					slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
				}

				UHorizontalBoxSlot* slot3 = Cast<UHorizontalBoxSlot>(HBox_Child->GetSlots()[1]);
				ensure(slot3 != nullptr);
				if (slot3 != nullptr)
				{
					slot3->SetPadding(FMargin(600, 0, 150, 0));
					slot3->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Left);
					slot3->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
				}
			}
		}
	}
}
