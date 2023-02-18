// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Battle_First_Widget.h"
#include "Battle_Log_Widget.h"
#include "Battle_State.h"
#include "Components/Spacer.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Battle_Command_Widget.h"
#include "../PlayerDataAsset.h"
#include "../EnemyDataAsset.h"
#include "../DragonQuest8_likeGameMode.h"
#include "../DragonQuest8_likeCharacter.h"
#include "BattleGameModeBase.generated.h"


#define DURATION 2.0f
#define DEAD 1
#define ALIVE 0

/**
 *
 */
UCLASS()
class ABattleGameModeBase : public ADragonQuest8_likeGameMode
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
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void setState(Battle_State state);
	UFUNCTION(Blueprintcallable, Category = "Myfunc")

	void setBattleLogWidget(UBattle_Log_Widget* widget);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector> enemy_pos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AEnemyCharacter*> enemy_actors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 enemy_num;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FPlayerDataAssetRecord> player_infos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<ADragonQuest8_likeCharacter*> player_actors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* Sound_Finish;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* Sound_Battle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* audio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* Sound_Player_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* Sound_Enemy_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* Sound_Damage_Physics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* Sound_LevelUp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	int32 enemy_deadcount; // �|�����G�̐�








	~ABattleGameModeBase();
	virtual void Tick(float DeltaTime) override;




protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBattle_First_Widget* battle_first_w;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBattle_Command_Widget* battle_command_w;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBattle_Log_Widget* battle_log_w;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetupInput();
	void PressedB();
	void Command_Wait();
	void Attack();
	void Escape();
	void Disable();
	void Enable();
	void Init();
	void Nop();
	void Finish();
	void LevelUp();
	void Wait();
	void Animation();
	void AnimationFinished();
	void Stack_Sort();
	void OpenField();
	bool Execute_Attack();
	bool Calculate_PlayerAttack(FPlayerDataAssetRecord player);
	bool Calculate_EnemyAttack(FEnemyDataAssetRecord enemy);

	UWidgetSwitcher* switcher;
	int32 enemy_id;
	UDQ8GameInstance* instance;
	TArray<int32> enemy_array;
	int32 player_deadcount; // �|���ꂽ�v���C���[�̐�
	TSet<int32> dead_id; // �|�����G��ID
	TArray<ADragonQuest8_likeCharacter*> player_order; // ���Ԃ����߂�L���[
	TArray<AEnemyCharacter*> enemy_order;
	bool first; // Attack�ň��ڂ����L���[���쐬
	int32 sum_exp; // �l�����v�o���l

	/* �f�o�b�O�p */
	void PressedD();
	void PressedK();
	int32 kill;




};
