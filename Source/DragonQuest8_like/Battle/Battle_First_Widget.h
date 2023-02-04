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
#include "../PlayerDataAsset.h"
#include "Battle_First_Widget.generated.h"

#define INDEX_HP 0
#define INDEX_MP 1
#define INDEX_Lv 2


USTRUCT(BlueprintType)
struct FPlayerText
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* HP_Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

		UTextBlock* MP_Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

		UTextBlock* Lv_Text;


};

UCLASS()
class UBattle_First_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* Sound_Select;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* Sound_Nigeru;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UWidgetSwitcher* Battle_Switcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FPlayerText> Texts;


	UBattle_First_Widget(const FObjectInitializer& ObjectInitializer);
	UWidgetSwitcher* getSwitcher();
	void Init(TMap<int32, FPlayerDataAssetRecord> player_infos);
	void Update(TMap<int32, FPlayerDataAssetRecord> player_infos);
	void Command_Wait();


protected:
	UFUNCTION(BlueprintCallable, Category = "Myfunc")
		void TatakauButton_Clicked();

	UFUNCTION(BlueprintCallable, Category = "Myfunc")
		void Change_State();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;

private:


};
