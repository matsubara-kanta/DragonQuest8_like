// Fill out your copyright notice in the Description page of Project Settings.


#include "DQ8GameInstance.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"

UDQ8GameInstance* UDQ8GameInstance::GetInstance()
{
    UDQ8GameInstance* instance = nullptr;

    if (GEngine)
    {
        FWorldContext* context = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
        instance = Cast<UDQ8GameInstance>(context->OwningGameInstance);
    }

    return instance;
}


void UDQ8GameInstance::DisplayDebugMessage(FString message)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, message);
    }
}

void UDQ8GameInstance::Load_Enemy()
{
    FSoftObjectPath EnemyDataAssetPath = "/Script/DragonQuest8_like.EnemyDataAsset'/Game/DragonQuest8_like/EnemyDataAsset.EnemyDataAsset'";

    if (enemy_asset == nullptr)
    {
        enemy_asset = Cast<UEnemyDataAsset>(StaticLoadObject(UEnemyDataAsset::StaticClass(), nullptr, *EnemyDataAssetPath.ToString()));
        ensure(enemy_asset != nullptr);
    }
    return;
}

void UDQ8GameInstance::Load_Player()
{
    FSoftObjectPath PlayerDataAssetPath = "/Script/DragonQuest8_like.PlayerDataAsset'/Game/DragonQuest8_like/PlayerDataAsset.PlayerDataAsset'";

    if (player_asset == nullptr)
    {
        player_asset = Cast<UPlayerDataAsset>(StaticLoadObject(UPlayerDataAsset::StaticClass(), nullptr, *PlayerDataAssetPath.ToString()));
        ensure(player_asset != nullptr);
    }
    return;
}

void UDQ8GameInstance::Player_Infos_Init()
{
        Load_Player();

        if (player_asset != nullptr && player_infos.Num() == 0)
        {
        	UKismetSystemLibrary::PrintString(this, "load_player_data", true, true, FColor::Cyan, 3.f, TEXT("None"));
        	for (int32 index = 0; index < player_asset->Data.Num(); index++) // プレイヤーのパラメータ初期化
        	{
        		player_infos.Add(player_asset->Data[index]);
        	}

        }

}

void UDQ8GameInstance::Enemy_Infos_Init()
{
    Load_Enemy();

    if (enemy_asset != nullptr && enemy_infos.Num() == 0)
    {
        UKismetSystemLibrary::PrintString(this, "load_enemy_data", true, true, FColor::Cyan, 3.f, TEXT("None"));
        for (int32 index = 0; index < enemy_asset->Data.Num(); index++)
        {
            enemy_infos.Add(enemy_asset->Data[index]); 
        }
    }
}
