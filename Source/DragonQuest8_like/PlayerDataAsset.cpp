// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDataAsset.h"

void UPlayerDataAsset::Import()
{
#if WITH_EDITORONLY_DATA
    if (!DataTable ||
        !DataTable->GetRowStruct()->IsChildOf(FPlayerData::StaticStruct()))
    {
        return;
    }

    Data.Empty();
    auto Names = DataTable->GetRowNames();

    for (int i = 0; i < Names.Num(); i++)
    {
        auto record = DataTable->FindRow<FPlayerData>(Names[i], FString());

        FPlayerDataAssetRecord asset;
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
        asset.NEXTLv_EXP = record->NEXTLv_EXP;
        asset.NAME = FText::FromName(Names[i]);
        Data.Add(asset);
    }

#endif
}