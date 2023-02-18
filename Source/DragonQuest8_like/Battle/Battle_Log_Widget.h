// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Battle_Log_Widget.generated.h"

/**
 * 
 */
UCLASS()
class DRAGONQUEST8_LIKE_API UBattle_Log_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBattle_Log_Widget(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)

		UTextBlock* log_text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

		UTextBlock* log_dead_text;


	void Update(FString str);
	void Dead_Update(FString str,float time);
	void Init();
	void Dead_Finish(FString str);
	void Collapsed();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;

};
