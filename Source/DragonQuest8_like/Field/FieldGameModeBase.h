// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../PlayerDataAsset.h"
#include "../DQ8GameInstance.h"
#include "FieldGameModeBase.generated.h"


#define INTERVAL 60*3
#define MAXRANGE 9
#define MINRANGE 0
#define ENEMY_MAX_NUM 10 // スポーンできる敵の最大値
#define ENEMY_MAX_CLASS 6 // 敵の種類の数

/**
 *
 */
UCLASS()
class DRAGONQUEST8_LIKE_API AFieldGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFieldGameModeBase();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<int32,FEnemyDataAssetRecord> enemy_infos;


	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int32 enemy_num;
	TMap<int32,FPlayerDataAssetRecord> player_infos;

	void Player_Location_Init();
	void Spawn_Enemy();
	void Enemy_Infos_Init();

};
