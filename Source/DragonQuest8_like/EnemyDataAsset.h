// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "EnemyDataAsset.generated.h"

/**
 *
 */
USTRUCT()
struct FEnemyData : public FTableRowBase
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
		int32 STATE = 0; // ÉLÉÉÉâÇÃèÛë‘
	UPROPERTY(EditAnywhere)
		int32 ID = 0;
	UPROPERTY(EditAnywhere)
		int32 EXP = 0;
	UPROPERTY(EditAnywhere)
		int32 GOLD = 0;

	UPROPERTY(EditAnywhere)
		UClass* myclass = nullptr;

	UPROPERTY(EditAnywhere)
		float dead_time = 0.0f;

	UPROPERTY(EditAnywhere)
		float attack_time = 0.0f;

};


USTRUCT(BlueprintType)

struct FEnemyDataAssetRecord
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 HP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Lv = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 ATK = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 DEF = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 INT = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SPD = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 STATE = 0; // ÉLÉÉÉâÇÃèÛë‘
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)

		int32 EXP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)

		int32 GOLD = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText NAME = FText::FromString("");

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UClass* myclass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float dead_time = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float attack_time = 0.0f;

};

UCLASS()
class UEnemyDataAsset : public UDataAsset
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
		TArray<FEnemyDataAssetRecord> Data;

};
