// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Battle_First_Widget.h"
#include "Battle_State.h"
#include "Components/Spacer.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Battle_Command_Widget.h"
#include "../PlayerDataAsset.h"
#include "../EnemyDataAsset.h"
#include "BattleGameModeBase.generated.h"


#define DURATION 2.0f

/**
 *
 */
UCLASS()
class ABattleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABattleGameModeBase();

	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void setEnemyLocation();
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		TArray<AEnemyCharacter*> getEnemyActors();
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void addEnemyActor(AEnemyCharacter* character);
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void setBattleCommandWidget(UBattle_Command_Widget* widget);
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		UBattle_Command_Widget* getBattleCommandWidget();
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void setBattleFirstWidget(UBattle_First_Widget* widget);
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		UBattle_First_Widget* getBattleFirstWidget();
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void Init_Player();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector> enemy_pos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AEnemyCharacter*> enemy_actors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 enemy_num;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FPlayerDataAssetRecord> player_infos;



	~ABattleGameModeBase();
	virtual void Tick(float DeltaTime) override;










protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBattle_First_Widget* battle_first_w;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBattle_Command_Widget* battle_command_w;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetupInput();
	void PressedB();
	void Command_Wait();
	void Attack();
	void Escape();

	UWidgetSwitcher* switcher;
	int32 enemy_id;
	UDQ8GameInstance* instance;

	/* デバッグ用 */
	void PressedD();
	void PressedK();
	int32 kill;




};
