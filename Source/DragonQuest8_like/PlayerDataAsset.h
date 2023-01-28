// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "PlayerDataAsset.generated.h"

/**
 *
 */

USTRUCT()
struct FPlayerData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		int32 HP = 0;
	UPROPERTY(EditAnywhere)
		int32 MP = 0;
	UPROPERTY(EditAnywhere)
		int32 Lv = 0;
	UPROPERTY(EditAnywhere)
		int32 ATK = 0;
	UPROPERTY(EditAnywhere)
		int32 DEF = 0;
	UPROPERTY(EditAnywhere)
		int32 INT = 0;
	UPROPERTY(EditAnywhere)
		int32 SPD = 0;
	UPROPERTY(EditAnywhere)
		int32 STATE = 0; // キャラの状態
	UPROPERTY(EditAnywhere)
		int32 ID = 0;
	UPROPERTY(EditAnywhere)
		int32 EXP = 0;
	UPROPERTY(EditAnywhere)
		int32 NEXTLv_EXP = 0; // レベルアップするのに必要な経験値

};


USTRUCT(BlueprintType)
struct FPlayerDataAssetRecord
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 HP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 MP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Lv = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 ATK = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 DEF = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 INT = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 SPD = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 STATE = 0; // キャラの状態
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 ID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 EXP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 NEXTLv_EXP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText NAME = FText::FromString("");
};


UCLASS()
class DRAGONQUEST8_LIKE_API UPlayerDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Param")
		UDataTable* DataTable;
#endif
	UFUNCTION(meta = (CallInEditor = "true"))
		void Import();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FPlayerDataAssetRecord> Data;

};
