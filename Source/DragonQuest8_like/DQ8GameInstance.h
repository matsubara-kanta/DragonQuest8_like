// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Field/PlayerDataAsset.h"
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

};
