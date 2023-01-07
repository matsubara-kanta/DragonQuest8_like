// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "Battle_First_Widget.h"
#include <Battle_State.h>
#include <Components/WidgetSwitcher.h>
#include "BattleActor.generated.h"

#define DURATION 2.0f


UCLASS()
class ABattleActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABattleActor();
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
		TSubclassOf<UUserWidget> WBP_Battle_First;
	UBattle_First_Widget* Battle_First_w;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetupInput();
	void PressedSpaceBar();
	void PressedB();
	void PrintStructure(const FEnemy& enemy);
	void PressedActionPrintStructure();
	void Command_Wait();
	void Attack();
	void Escape();

	TArray<FEnemy> Enemy_Infos = { {10,10,10,10,10,10,10,1,"Corpse_Melee",true},
	{20,20,20,20,20,20,20,2,"Corpse_Sword",true},{30,30,30,30,30,30,30,3,"Large_Sword3",true} };

};
