// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameModeBase.h"
#include "../DQ8GameInstance.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

Battle_State state = Battle_State::Command_Wait;

// Sets default values
ABattleGameModeBase::ABattleGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.0f;

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/DragonQuest8_like/MyDragonQuest8_likeCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	instance = UDQ8GameInstance::GetInstance();
}

ABattleGameModeBase::~ABattleGameModeBase()
{

}

// Called when the game starts or when spawned
void ABattleGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SetupInput();
	enemy_id = 0;
	kill = 0;
	enemy_deadcount = 0;
	player_deadcount = 0;
	state = Battle_State::Init;
}

// Called every frame
void ABattleGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (state)
	{
	case Battle_State::Command_Wait:
		Command_Wait();
		break;
	case Battle_State::Attack:
		Attack();
		break;
	case Battle_State::Escape:
		Escape();
		break;
	case Battle_State::Disable:
		Disable();
		break;
	case Battle_State::Enable:
		Enable();
		break;
	case Battle_State::Finish:
		Finish();
		break;
	case Battle_State::Init:
		Init();
		break;
	case Battle_State::Nop:
		break;
	default:
		break;
	}

}

void ABattleGameModeBase::PressedB()
{
	int32 index = switcher->GetActiveWidgetIndex();
	if (0 < index)
	{

		if (battle_command_w->is_Spacer_Visible())
		{
			battle_command_w->backCommand();
		}
		else
		{
			switcher->SetActiveWidgetIndex(index - 1);
			battle_command_w->Dec_EnemyArray();
		}
	}
	UKismetSystemLibrary::PrintString(this, "PressedB");
	battle_command_w->setkougekiButton(true);
}

void ABattleGameModeBase::PressedD()
{


	for (int32 index = 0; index < player_actors.Num(); ++index)
	{
		player_actors[index]->Print_All_Infos();
	}

	UKismetSystemLibrary::PrintString(this, "player:", true, true, FColor::Cyan, 10.0f);


	UKismetSystemLibrary::PrintString(this, "\n", true, true, FColor::Cyan, 10.0f);
	for (int32 index = 0; index < enemy_actors.Num(); ++index)
	{
		enemy_actors[index]->Print_All_Infos();
	}
	UKismetSystemLibrary::PrintString(this, "enemy:", true, true, FColor::Cyan, 10.0f);


	UKismetSystemLibrary::PrintString(this, "PressedD");
}

void ABattleGameModeBase::PressedK()
{
	if (kill < enemy_actors.Num()) {
		enemy_actors[kill]->Destroy();
		kill++;
	}
	UKismetSystemLibrary::PrintString(this, "PressedK");
}

void ABattleGameModeBase::SetupInput()
{
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	InputComponent->BindKey(EKeys::B, IE_Pressed, this, &ABattleGameModeBase::PressedB);
	InputComponent->BindKey(EKeys::D, IE_Pressed, this, &ABattleGameModeBase::PressedD);
	InputComponent->BindKey(EKeys::K, IE_Pressed, this, &ABattleGameModeBase::PressedK);
}

void ABattleGameModeBase::setEnemyLocation()
{
	FVector pos = FVector(600, 0, 90);
	FVector prev = pos;
	FRotator rotate = FRotator(0, -180, 0);
	int32 count = 1;
	if (enemy_num % 2 != 0) // 敵の数が奇数の時
	{
		int32 ratio = 0;

		if (1 < enemy_num)
			ratio = MAX_POS_R / ((enemy_num - 1) / 2);

		for (int32 index = 0; index < enemy_num; ++index)
		{

			FVector p;
			if (index % 2 != 0) // 右側に配置
			{
				p = pos + FVector(0, ratio * count, 0);
				prev = p;
				count++;
			}
			else // 左側に配置
			{
				p = FVector(prev.X, -prev.Y, prev.Z);
			}
			enemy_pos.Add(p);
		}
	}
	else // 敵の数が偶数の時
	{
		int32 ratio = MAX_POS_R / enemy_num;
		for (int32 index = 0; index < enemy_num; ++index)
		{
			FVector p;

			if (index % 2 != 0) // 左側に配置
			{
				p = FVector(prev.X, -prev.Y, prev.Z);
			}
			else // 右側に配置
			{
				p = prev + FVector(0, ratio * count, 0);
				prev = p;
				count++;
			}

			enemy_pos.Add(p);
		}

	}
}

void  ABattleGameModeBase::addEnemyActor(AEnemyCharacter* character)
{
	character->setID(enemy_id);
	enemy_id++;
	enemy_actors.Add(character);
}

TArray<AEnemyCharacter*> ABattleGameModeBase::getEnemyActors()
{
	return enemy_actors;
}

void  ABattleGameModeBase::setBattleCommandWidget(UBattle_Command_Widget* widget)
{
	battle_command_w = widget;
	ensure(battle_command_w);
	if (battle_command_w != nullptr)
	{
		switcher->AddChild(battle_command_w);
	}

}

UBattle_Command_Widget* ABattleGameModeBase::getBattleCommandWidget()
{
	return battle_command_w;
}

void  ABattleGameModeBase::setBattleFirstWidget(UBattle_First_Widget* widget)
{
	battle_first_w = widget;
	ensure(battle_first_w);
	if (battle_first_w != nullptr)
	{
		switcher = battle_first_w->getSwitcher();
		ensure(switcher);
	}

}

UBattle_First_Widget* ABattleGameModeBase::getBattleFirstWidget()
{
	return battle_first_w;
}

void ABattleGameModeBase::Init_Player()
{
	/* プレイヤーの初期化 */
	battle_first_w->Init_Player(instance->player_infos);
}

/* 連続入力されたくないとき */
void ABattleGameModeBase::Disable()
{
	this->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	battle_command_w->Disable();
}

/* 攻撃が終了したときの初期化 */
void ABattleGameModeBase::Init()
{
	battle_first_w->Init();
	battle_command_w->Init(player_actors.Num() - player_deadcount, dead_id);
	state = Battle_State::Command_Wait;
	UKismetSystemLibrary::PrintString(this, "Command_Wait", true, true, FColor::Red, 10.f, TEXT("None"));

}

void ABattleGameModeBase::Command_Wait()
{
	battle_first_w->Command_Wait();
	battle_command_w->Command_Wait(player_actors);
}

void ABattleGameModeBase::Attack()
{
	if (player_order.Num() == 0)
	{
		enemy_array = battle_command_w->getArray();
		battle_first_w->Attack();

		/* 敵味方をスタックに */
		for (int32 index = 0; index < player_actors.Num() - player_deadcount; index++)
		{
			player_order.Add(player_actors[index]);
		}

		for (int32 index = 0; index < enemy_num - enemy_deadcount; index++)
		{
			enemy_order.Add(enemy_actors[index]);
		}

		/* それぞれのスタックを素早さ順にソート */

		Stack_Sort();

		/* ポップした順に攻撃を決めて実行　*/

		Execute_Attack();

		if (enemy_num == enemy_deadcount)
		{
			TFunction<void(void)> Func = [this]() {
				state = Battle_State::Finish;
			};
			FTimerHandle Handle;
			FTimerManager& timerManager = GetWorld()->GetTimerManager();
			GetWorld()->GetTimerManager().SetTimer(Handle, (TFunction<void(void)>&&)Func, 2.0f, false);
			state = Battle_State::Nop;
			UKismetSystemLibrary::PrintString(this, "Finish", true, true, FColor::Red, 10.f, TEXT("None"));
		}
		else
		{
			state = Battle_State::Init;
			UKismetSystemLibrary::PrintString(this, "Init", true, true, FColor::Red, 10.f, TEXT("None"));
		}

	}

}

void ABattleGameModeBase::Escape()
{
	this->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}
void ABattleGameModeBase::Enable()
{
	this->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	state = Battle_State::Command_Wait;

}


void ABattleGameModeBase::Stack_Sort()
{
	// 敵見方で一番早いやつだけ取ってくればいい
	/* プレイヤーを素早さ順にソート */
	player_order.Sort([](ADragonQuest8_likeCharacter& A, ADragonQuest8_likeCharacter& B)
		{
			return A.getRecord().SPD > B.getRecord().SPD;
		});

	/* 敵を素早さ順にソート */

	enemy_order.Sort([](AEnemyCharacter& A, AEnemyCharacter& B)
		{
			return A.getRecord().SPD > B.getRecord().SPD;
		});

}

void ABattleGameModeBase::Execute_Attack()
{
	while (!player_order.IsEmpty() || !enemy_order.IsEmpty())
	{
		/* 両方のスタックが空で無い時 */
		if (!player_order.IsEmpty() && !enemy_order.IsEmpty())
		{
			ADragonQuest8_likeCharacter* player = player_order.Top();
			AEnemyCharacter* enemy = enemy_order.Top();
			FPlayerDataAssetRecord p = player->getRecord();
			FEnemyDataAssetRecord e = enemy->getRecord();
			if (p.SPD >= e.SPD)
			{
				Calculate_PlayerAttack(p);
				player_order.Pop();
			}
			else
			{
				Calculate_EnemyAttack(e);
				enemy_order.Pop();
			}
		}
		else if (player_order.IsEmpty()) // プレイヤーが全員攻撃し終わっているとき
		{
			Calculate_EnemyAttack(enemy_order.Pop()->getRecord());
		}
		else // 敵が全員攻撃し終わっているとき
		{
			Calculate_PlayerAttack(player_order.Pop()->getRecord());
		}
	}
}

void ABattleGameModeBase::Calculate_PlayerAttack(FPlayerDataAssetRecord player)
{
	int32 index = enemy_array[player.ID];
	FEnemyDataAssetRecord enemy = enemy_actors[index]->getRecord();
	if (player.STATE == ALIVE && enemy.STATE == ALIVE)
	{
		int32 damageA = player.ATK / 2 - enemy.DEF / 4;
		int32 random = damageA / 16 + 1;
		int32 result = damageA + random;

		/* 回復してしまうのを防ぐ */
		if (result < 0)
			result = 0;

		enemy.HP = enemy.HP - result;
		if (enemy.HP < 0)
			enemy.HP = 0;
		UKismetSystemLibrary::PrintString(this, "damage_toEnemy: " + FString::FromInt(result), true, true, FColor::Cyan, 10.f, TEXT("None"));

		enemy_actors[index]->setRecord(enemy);

		enemy_actors[index]->Damaged();

		/* 死亡処理 */
		if (enemy.HP == 0)
		{
			enemy.STATE = DEAD;
			enemy_deadcount++;
			UKismetSystemLibrary::PrintString(this, "deadcount: " + FString::FromInt(enemy_deadcount), true, true, FColor::Yellow, 10.f, TEXT("None"));
			dead_id.Add(enemy.ID);
			enemy_actors[index]->setRecord(enemy);
			enemy_actors[index]->Dead();
		}



	}
}

void ABattleGameModeBase::Calculate_EnemyAttack(FEnemyDataAssetRecord enemy)
{
	int32 index = FMath::RandRange(0, player_actors.Num() - 1);
	FPlayerDataAssetRecord player = player_actors[index]->getRecord();
	if (player.STATE == ALIVE && enemy.STATE == ALIVE)
	{
		int32 damageA = enemy.ATK / 2 - player.DEF / 4;
		int32 random = damageA / 16 + 1;
		int32 result = damageA + random;
		if (result < 0)
			result = 0;
		player.HP = player.HP - result;
		if (player.HP < 0)
			player.HP = 0;

		UKismetSystemLibrary::PrintString(this, "damage_toPlayer: " + FString::FromInt(result), true, true, FColor::Cyan, 10.f, TEXT("None"));
		instance->player_infos.Find(player.ID)->HP -= result;
		battle_first_w->Update(instance->player_infos);
		player_actors[index]->setRecord(player);


		if (player.HP == 0)
		{
			player.STATE = DEAD;
			player_actors[index]->setRecord(player);
			player_actors[player.ID]->Destroy();
			player_deadcount++;
		}

	}
}

void ABattleGameModeBase::Finish()
{
	audio->Stop();
	UGameplayStatics::PlaySound2D(GetWorld(), Sound_Finish);
	TFunction<void(void)> Func = [this]() {
		UGameplayStatics::OpenLevel(GetWorld(), "Field", true);
	};
	FTimerHandle Handle;
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	GetWorld()->GetTimerManager().SetTimer(Handle, (TFunction<void(void)>&&)Func, 3.0f, false);
	state = Battle_State::Nop;
}