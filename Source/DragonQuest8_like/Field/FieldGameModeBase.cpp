// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAL/PlatformProcess.h"
#include "GameFramework/Character.h"
#include "../DQ8GameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values
AFieldGameModeBase::AFieldGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/DragonQuest8_like/MyDragonQuest8_likeCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

// Called when the game starts or when spawned
void AFieldGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	/* デバッグ用 */

	UDQ8GameInstance* instance = UDQ8GameInstance::GetInstance();
	if (instance)
	{
		instance->Player_Infos_Init();
		instance->Enemy_Infos_Init();
	}

	Player_Location_Init();
	Enemy_Infos_Init();
	Spawn_Enemy();
}

// Called every frame
void AFieldGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AFieldGameModeBase::Player_Location_Init()
{
	UDQ8GameInstance* instance = UDQ8GameInstance::GetInstance();
	ensure(instance != nullptr);
	if (instance)
	{
		UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0)->SetActorLocation(instance->player_pos); // プレイヤーのスポーン位置を設定
	}

}

void AFieldGameModeBase::Enemy_Infos_Init()
{
	UDQ8GameInstance* instance = UDQ8GameInstance::GetInstance();
	ensure(instance);
	enemy_num = FMath::RandRange(1, ENEMY_MAX_NUM);

	if (instance->enemy_infos.Num() != 0)
	{
		for (int32 index = 0; index < enemy_num; index++)
		{
			enemy_infos.Add(instance->enemy_infos[FMath::RandRange(0, ENEMY_MAX_CLASS - 1)]); // ランダムスポーン
		}
	}
}

void AFieldGameModeBase::Spawn_Enemy()
{
	FVector pos = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0)->GetActorLocation();
	pos = FVector(pos.X, pos.Y, 0);
	ensure(enemy_infos.Num() != 0);
	for (int32 index = 0; index < enemy_num; ++index)
	{
		FString str = enemy_infos[index].NAME.ToString() + "_BP";
		FString name = str + "." + str + "_C'";
		FString path = "/Script/Engine.Blueprint'/Game/DragonQuest8_like/Scenes/Field/Enemy/" + name;
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
		}
	}
}