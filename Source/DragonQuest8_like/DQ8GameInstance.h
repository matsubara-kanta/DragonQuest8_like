// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayerDataAsset.h"
#include "EnemyDataAsset.h"
#include "DQ8GameInstance.generated.h"

/**
 *
 */
UCLASS()
class DRAGONQUEST8_LIKE_API UDQ8GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		TMap<int32,FPlayerDataAssetRecord> player_infos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		FVector player_pos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		 UPlayerDataAsset* player_asset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		int32 enemy_id; // 当たった敵をバトルでもスポーンさせる

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TMap<int32,FEnemyDataAssetRecord> enemy_infos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		 UEnemyDataAsset* enemy_asset;

	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void Player_Infos_Init();

	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void Enemy_Infos_Init();

	UFUNCTION(Blueprintcallable, Category = "Myfunc")

		void Print_All_Infos();


	static UDQ8GameInstance* GetInstance();

};
