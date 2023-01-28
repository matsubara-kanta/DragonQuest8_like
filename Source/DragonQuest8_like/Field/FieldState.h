// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../PlayerDataAsset.h"
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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int32 enemy_num;
	TArray<FEnemyDataAssetRecord> enemy_infos;
	TArray<FPlayerDataAssetRecord> player_infos;

	void Player_Location_Init();
	void Spawn_Enemy();
	void Enemy_Infos_Init();



};
