// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAL/PlatformProcess.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values
AFieldState::AFieldState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFieldState::BeginPlay()
{
	Super::BeginPlay();
	count = 0;
	Player_Infos_Init();
	Enemy_Infos_Init();
	Spawn_Enemy();
}

// Called every frame
void AFieldState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFieldState::Load_Player()
{
	FSoftObjectPath PlayerDataAssetPath = "/Script/DragonQuest8_like.PlayerDataAsset'/Game/DragonQuest8_like/Scenes/Field/PlayerDataAsset.PlayerDataAsset'";

	if (player_asset == nullptr)
	{
		player_asset = Cast<UPlayerDataAsset>(StaticLoadObject(UPlayerDataAsset::StaticClass(), nullptr, *PlayerDataAssetPath.ToString()));
		ensure(player_asset != nullptr);
	}
	return;
}


void AFieldState::Player_Infos_Init()
{
	UDQ8GameInstance* instance = UDQ8GameInstance::GetInstance();
	ensure(instance != nullptr);
	if (instance && instance->player_infos.IsEmpty())
	{

		Load_Player();

		if (player_asset != nullptr)
		{
			//UKismetSystemLibrary::PrintString(this, "found_asset", true, true, FColor::Cyan, 50.f, TEXT("None"));
				//UKismetSystemLibrary::PrintString(this, "found_instance", true, true, FColor::Cyan, 50.f, TEXT("None")); 
			for (int32 index = 0; index < player_asset->Data.Num(); index++) // プレイヤーのパラメータ初期化
			{
				instance->player_infos.Add(player_asset->Data[index]);
			}

		}
	}
	UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0)->SetActorLocation(instance->player_pos); // プレイヤーのスポーン位置を設定

}



void AFieldState::DisplayByStaticmethod()
{
	UDQ8GameInstance* instance = UDQ8GameInstance::GetInstance();
	if (instance)
	{
		instance->DisplayDebugMessage(FString("DisplayByStaticmethod"));
	}
}

void AFieldState::DisplayByActor()
{
	UDQ8GameInstance* instance = Cast<UDQ8GameInstance>(GetGameInstance());
	if (instance)
	{
		instance->DisplayDebugMessage("DisplayByActor");
	}
}



void AFieldState::Load_Enemy()
{
	FSoftObjectPath EnemyDataAssetPath = "/Script/DragonQuest8_like.EnemyDataAsset'/Game/DragonQuest8_like/Scenes/Field/EnemyDataAsset.EnemyDataAsset'";

	if (enemy_asset == nullptr)
	{
		enemy_asset = Cast<UEnemyDataAsset>(StaticLoadObject(UEnemyDataAsset::StaticClass(), nullptr, *EnemyDataAssetPath.ToString()));
		ensure(enemy_asset != nullptr);
	}
	return;
}

void AFieldState::Enemy_Infos_Init()
{
	Load_Enemy();
	enemy_num = FMath::RandRange(1, ENEMY_MAX_NUM);
	UKismetSystemLibrary::PrintString(this, FString::FromInt(enemy_num), true, true, FColor::Cyan, 50.f, TEXT("None"));

	if (enemy_asset != nullptr)
	{
		for (int32 index = 0; index < enemy_num; index++)
		{
			enemy_infos.Add(enemy_asset->Data[FMath::RandRange(0, ENEMY_MAX_CLASS - 1)]); // ランダムスポーン
		}
	}
}

void AFieldState::Spawn_Enemy()
{
	FVector pos = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0)->GetActorLocation();
	pos = FVector(pos.X, pos.Y, 0);
	for (int32 index = 0; index < enemy_num; ++index)
	{
		FString str = enemy_infos[index].NAME.ToString() + "_BP";
		FString name = str + "." + str + "_C'";
		FString path = "/Script/Engine.Blueprint'/Game/DragonQuest8_like/Scenes/Battle/Enemy/" + name;
		TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous(); // 上記で設定したパスに該当するクラスを取得
		if (sc != nullptr)
		{
			AActor* a = GetWorld()->SpawnActor<AActor>(sc); // スポーン処理

			int32 x = FMath::RandRange(-2000, 2000);
			while (-200 < x && x < 200)
				x = FMath::RandRange(-2000, 2000);

			int32 y = FMath::RandRange(-600, 600);
			while (-200 < y && y < 200)
				y = FMath::RandRange(-600, 600);

			a->SetActorLocation(pos + FVector(x, y, 0));
			a->SetActorLabel(FString::FromInt(enemy_infos[index].ID));
		}
	}
}