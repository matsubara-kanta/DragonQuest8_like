// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerDataAsset.h"
#include "EnemyDataAsset.h"
#include "../DQ8GameInstance.h"
#include "FieldState.generated.h"

#define INTERVAL 60*3
#define MAXRANGE 9
#define MINRANGE 0
#define ENEMY_MAX_NUM 10
#define ENEMY_MAX_CLASS 6


UCLASS()
class AFieldState : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFieldState();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(meta = (CallInEditor = "true"), Category = "test")
		void DisplayByStaticmethod();

	UFUNCTION(meta = (CallInEditor = "true"), Category = "test")
		void DisplayByActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int count;
	int32 enemy_num;

	UPROPERTY()
		TSoftObjectPtr<class UPlayerDataAsset> player_asset;
	UPROPERTY()
		TSoftObjectPtr<class UEnemyDataAsset> enemy_asset;
	TArray<FPlayerDataAssetRecord> player_infos;
	TArray<FEnemyDataAssetRecord> enemy_infos;

	void Load_Player();
	void Player_Infos_Init();
	void Spawn_Enemy();
	void Enemy_Infos_Init();
	void Load_Enemy();



};
