// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDataAsset.h"

void UEnemyDataAsset::Import()
{
#if WITH_EDITORONLY_DATA
    if (!DataTable ||
        !DataTable->GetRowStruct()->IsChildOf(FEnemyData::StaticStruct()))
    {
        return;
    }

    Data.Empty();
    auto Names = DataTable->GetRowNames();

    for (int i = 0; i < Names.Num(); i++)
    {
        auto record = DataTable->FindRow<FEnemyData>(Names[i], FString());

        FEnemyDataAssetRecord asset;
        asset.HP = record->HP;
        asset.MP = record->MP;
        asset.Lv = record->Lv;
        asset.ATK = record->ATK;
        asset.DEF = record->DEF;
        asset.INT = record->INT;
        asset.SPD = record->SPD;
        asset.STATE = record->STATE;
        asset.ID = record->ID;
        asset.EXP = record->EXP;
        asset.GOLD = record->GOLD;
        asset.NAME = FText::FromName(Names[i]);
        asset.myclass = record->myclass;
        Data.Add(asset);
    }

#endif
}