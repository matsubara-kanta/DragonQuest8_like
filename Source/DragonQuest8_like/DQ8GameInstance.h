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
	static UDQ8GameInstance* GetInstance();
	void DisplayDebugMessage(FString message);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		TArray<FPlayerDataAssetRecord> player_infos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		FVector player_pos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		int32 enemy_id; // 当たった敵をバトルでもスポーンさせる
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TArray<FEnemyDataAssetRecord> enemy_infos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSoftObjectPtr<class UEnemyDataAsset> enemy_asset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		TSoftObjectPtr<class UPlayerDataAsset> player_asset;


	UFUNCTION(Blueprintcallable)
		void Load_Enemy();
	UFUNCTION(Blueprintcallable)
		void Load_Player();
	UFUNCTION(Blueprintcallable)
		void Player_Infos_Init();
	UFUNCTION(Blueprintcallable)
		void Enemy_Infos_Init();



};
