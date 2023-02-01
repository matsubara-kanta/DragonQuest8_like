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

void UDQ8GameInstance::Player_Infos_Init()
{
	if (player_asset != nullptr && player_infos.Num() == 0)
	{
		for (int32 index = 0; index < player_asset->Data.Num(); index++) // プレイヤーのパラメータ初期化
		{
			player_infos.Add(index,player_asset->Data[index]);
		}

	}

}

void UDQ8GameInstance::Enemy_Infos_Init()
{
	if (enemy_asset != nullptr && enemy_infos.Num() == 0)
	{
		for (int32 index = 0; index < enemy_asset->Data.Num(); index++)
		{
			enemy_infos.Add(index,enemy_asset->Data[index]);
		}
	}
}


void UDQ8GameInstance::Print_All_Infos()
{
	for (int32 index = 0; index < player_infos.Num(); ++index)
	{
		UKismetSystemLibrary::PrintString(this, "HP:	 " + FString::FromInt(player_infos[index].HP) + "            MP:  " + FString::FromInt(player_infos[index].MP) + "            Lv:  " + FString::FromInt(player_infos[index].Lv) + "           ATK:  " + FString::FromInt(player_infos[index].ATK) + "         DEF:  " + FString::FromInt(player_infos[index].DEF) + "           INT:  " + FString::FromInt(player_infos[index].INT) + "         SPD:  " + FString::FromInt(player_infos[index].SPD) + "         STATE:  " + FString::FromInt(player_infos[index].STATE) + "           ID:  " + FString::FromInt(player_infos[index].ID) + "          NAME:  " + player_infos[index].NAME.ToString(), true, true, FColor::Cyan, 10.f, TEXT("None"));
	}

	UKismetSystemLibrary::PrintString(this, "player:", true, true, FColor::Cyan, 10.0f);

	UKismetSystemLibrary::PrintString(this, "\n", true, true, FColor::Cyan, 10.0f);
	for (int32 index = 0; index < enemy_infos.Num(); ++index)
	{
		UKismetSystemLibrary::PrintString(this, "HP:	 " + FString::FromInt(enemy_infos[index].HP) + "            MP:  " + FString::FromInt(enemy_infos[index].MP) + "            Lv:  " + FString::FromInt(enemy_infos[index].Lv) + "           ATK:  " + FString::FromInt(enemy_infos[index].ATK) + "         DEF:  " + FString::FromInt(enemy_infos[index].DEF) + "           INT:  " + FString::FromInt(enemy_infos[index].INT) + "         SPD:  " + FString::FromInt(enemy_infos[index].SPD) + "         STATE:  " + FString::FromInt(enemy_infos[index].STATE) + "           ID:  " + FString::FromInt(enemy_infos[index].ID) + "          NAME:  " + enemy_infos[index].NAME.ToString(), true, true, FColor::Cyan, 10.f, TEXT("None"));

	}
	UKismetSystemLibrary::PrintString(this, "enemy:", true, true, FColor::Cyan, 10.0f);

}