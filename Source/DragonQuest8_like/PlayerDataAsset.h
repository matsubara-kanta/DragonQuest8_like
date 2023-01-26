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
		int32 HP;
	UPROPERTY(EditAnywhere)
		int32 MP;
	UPROPERTY(EditAnywhere)
		int32 Lv;
	UPROPERTY(EditAnywhere)
		int32 ATK;
	UPROPERTY(EditAnywhere)
		int32 DEF;
	UPROPERTY(EditAnywhere)
		int32 INT;
	UPROPERTY(EditAnywhere)
		int32 SPD;
	UPROPERTY(EditAnywhere)
		int32 STATE; // キャラの状態
	UPROPERTY(EditAnywhere)
		int32 ID;
	UPROPERTY(EditAnywhere)
		int32 EXP;
	UPROPERTY(EditAnywhere)
		int32 NEXTLv_EXP; // レベルアップするのに必要な経験値

};


USTRUCT(BlueprintType)
struct FPlayerDataAssetRecord
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 HP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 MP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Lv;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 ATK;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 DEF;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 INT;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 SPD;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 STATE; // キャラの状態
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 EXP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 NEXTLv_EXP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText NAME;
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
