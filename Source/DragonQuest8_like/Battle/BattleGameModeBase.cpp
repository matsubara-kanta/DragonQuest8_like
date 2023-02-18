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

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/DragonQuest8_like/Player/MyDragonQuest8_likeCharacter"));
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
	sum_exp = 0;
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
		Nop();
		break;
	case Battle_State::Animation:
		Animation();
		break;
	case Battle_State::AnimationFinished:
		AnimationFinished();
		break;
	case Battle_State::LevelUp:
		LevelUp();
		break;
	case Battle_State::Wait:
		Wait();
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
void  ABattleGameModeBase::setBattleLogWidget(UBattle_Log_Widget* widget)
{
	battle_log_w = widget;
	ensure(battle_log_w);
	if (battle_log_w != nullptr)
	{
		switcher->AddChild(battle_log_w);
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
	first = true;
	battle_first_w->Init();
	battle_command_w->Init(player_actors.Num() - player_deadcount, dead_id);
	battle_log_w->Init();
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	state = Battle_State::Command_Wait;
	//UKismetSystemLibrary::PrintString(this, "Command_Wait", true, true, FColor::Red, 3.f, TEXT("None"));

}

void ABattleGameModeBase::Command_Wait()
{
	battle_first_w->Command_Wait();
	battle_command_w->Command_Wait(player_actors);
}

void ABattleGameModeBase::Attack()
{
	if (player_order.IsEmpty() && enemy_order.IsEmpty() && first)
	{
		/* バトルログ表示 */
		int32 i = switcher->GetActiveWidgetIndex();
		if (i < switcher->GetAllChildren().Num() - 1)
		{
			switcher->SetActiveWidgetIndex(i + 1);
			battle_log_w->SetVisibility(ESlateVisibility::Visible);
		}

		enemy_array = battle_command_w->getArray();
		battle_first_w->Attack();

		/* 敵味方をスタックに */
		for (int32 index = 0; index < player_actors.Num(); index++)
		{
				player_order.Add(player_actors[index]);
		}

		for (int32 index = 0; index < enemy_actors.Num(); index++)
		{
			//for (int32 id : dead_id)
			//{
			//	if (index != id)
			//		enemy_order.Add(enemy_actors[index]);
			//}
			if(enemy_actors[index]->getRecord().STATE != DEAD)
				enemy_order.Add(enemy_actors[index]);
		}

		/* それぞれのスタックを素早さ順にソート */

		Stack_Sort();
		first = false;
		dead_id.Empty();
	}

	if (!player_order.IsEmpty() || !enemy_order.IsEmpty())
	{
		/* ポップした順に攻撃を決めて実行　*/

		if (Execute_Attack())
		{
			/* アニメーションが終わるまで待つ */
			//UKismetSystemLibrary::PrintString(this, "Animation", true, true, FColor::Black, 3.f, TEXT("None"));

			state = Battle_State::Animation;
		}
		else
		{
			state = Battle_State::AnimationFinished;
		}

	}

	//UKismetSystemLibrary::PrintString(this, "Attack", true, true, FColor::Yellow, 3.f, TEXT("None"));
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

bool ABattleGameModeBase::Execute_Attack()
{
	/* 両方のキューが空で無い時 */
	if (!player_order.IsEmpty() && !enemy_order.IsEmpty())
	{
		FPlayerDataAssetRecord player = player_order[0]->getRecord();
		FEnemyDataAssetRecord enemy = enemy_order[0]->getRecord();
		//UKismetSystemLibrary::PrintString(this, player.NAME.ToString(), true, true, FColor::Cyan, 3.f, TEXT("None"));

		if (player.SPD >= enemy.SPD)
		{
			player_order.RemoveAt(0);
			return Calculate_PlayerAttack(player);
		}
		else
		{
			enemy_order.RemoveAt(0);
			return Calculate_EnemyAttack(enemy);
		}
	}
	else if (player_order.IsEmpty()) // プレイヤーが全員攻撃し終わっているとき
	{
		FEnemyDataAssetRecord enemy = enemy_order[0]->getRecord();
		enemy_order.RemoveAt(0);
		return Calculate_EnemyAttack(enemy);
	}
	else if (enemy_order.IsEmpty()) // 敵が全員攻撃し終わっているとき
	{
		FPlayerDataAssetRecord player = player_order[0]->getRecord();
		player_order.RemoveAt(0);
		return Calculate_PlayerAttack(player);
	}
	else
	{
		return false;
	}
}

bool ABattleGameModeBase::Calculate_PlayerAttack(FPlayerDataAssetRecord player)
{
	int32 index = enemy_array[player.ID];
	FEnemyDataAssetRecord enemy = enemy_actors[index]->getRecord();

	if (enemy.STATE == DEAD) // 攻撃対象が倒れていたらランダムな敵に攻撃
	{
		for (int32 i = 0; i < enemy_actors.Num(); i++)
		{
			if (enemy_actors[i]->getRecord().STATE == ALIVE)
			{
				index = i;
				enemy = enemy_actors[i]->getRecord();
				break;
			}
		}

	}

	if (player.STATE == ALIVE)
	{
		battle_log_w->Update(player.NAME.ToString() + " attacks!");
		int32 damageA = player.ATK / 2 - enemy.DEF / 4;
		int32 random = damageA / 16 + 1;
		int32 result = damageA + random;

		/* 回復してしまうのを防ぐ */
		if (result < 0)
			result = 0;

		enemy.HP = enemy.HP - result;
		if (enemy.HP < 0)
			enemy.HP = 0;

		FString str_hp = FString::Printf(TEXT("%d"), result);
		FString s = "Does " + str_hp + +" points of damage to " + enemy.NAME.ToString() + ".";
		FString ss = enemy.NAME.ToString() + " is defeated";
		TFunction<void(FString, int32, FString, float)> Func = [this](FString str, int32 hp, FString str2, float time) {
			battle_log_w->Update(str);
			if (hp == 0)
			{
				battle_log_w->Dead_Update(str2, time);
			}
		};
		FTimerHandle Handle;
		FTimerDelegate  TimerDelegate;
		TimerDelegate.BindLambda((TFunction<void(FString, int32, FString, float)>&&)Func, s, enemy.HP, ss, enemy.dead_time);
		GetWorld()->GetTimerManager().SetTimer(Handle, TimerDelegate, 2.f, false);

		enemy_actors[index]->setRecord(enemy);

		enemy_actors[index]->Damaged();

		/* 死亡処理 */
		if (enemy.HP == 0)
		{
			enemy.STATE = DEAD;
			dead_id.Add(enemy.ID);
			enemy_actors[index]->setRecord(enemy);
			//AEnemyCharacter* del = nullptr;
			//for (AEnemyCharacter* dead : enemy_order)
			//{
			//	if (dead->getRecord().ID == enemy.ID)
			//		del = dead;
			//}
			//if (del != nullptr)
			//	enemy_order.Remove(del);
			sum_exp += enemy.EXP;
		}

	}

	return true;
}

bool ABattleGameModeBase::Calculate_EnemyAttack(FEnemyDataAssetRecord enemy)
{

	int32 index = FMath::RandRange(0, player_actors.Num() - 1);
	FPlayerDataAssetRecord player = player_actors[index]->getRecord();

	if (player.STATE == ALIVE && enemy.STATE == ALIVE)
	{
		battle_log_w->Update(enemy.NAME.ToString() + " attacks!");
		int32 damageA = enemy.ATK / 2 - player.DEF / 4;
		int32 random = damageA / 16 + 1;
		int32 result = damageA + random;
		if (result < 0)
			result = 0;

		FString str_hp = FString::Printf(TEXT("%d"), result);
		FString s = "Does " + str_hp + +" points of damage to " + player.NAME.ToString() + ".";
		TFunction<void(FString)> Func = [this](FString str) {
			battle_log_w->Update(str);
		};
		FTimerHandle Handle;
		FTimerDelegate  TimerDelegate;
		TimerDelegate.BindLambda((TFunction<void(FString)>&&)Func, s);
		GetWorld()->GetTimerManager().SetTimer(Handle, TimerDelegate, 1.5f, false);


		player.HP = player.HP - result;
		if (player.HP < 0)
			player.HP = 0;

		//UKismetSystemLibrary::PrintString(this, "damage_toPlayer: " + FString::FromInt(result), true, true, FColor::Yellow, 3.f, TEXT("None"));
		instance->player_infos.Find(player.ID)->HP -= result;
		battle_first_w->Update(instance->player_infos);
		player_actors[index]->setRecord(player);
		enemy_actors[enemy.ID]->Attack();
		player_actors[index]->Damaged();


		if (player.HP == 0)
		{
			FString ss = player.NAME.ToString() + " is defeated";
			TFunction<void(FString, float)> Func2 = [this](FString str, float time) {
				battle_log_w->Dead_Update(str, time);
			};
			TimerDelegate.BindLambda((TFunction<void(FString, float)>&&)Func2, ss, 0.0f);
			GetWorld()->GetTimerManager().SetTimer(Handle, TimerDelegate, 1.5f, false);

			player.STATE = DEAD;
			player_actors[index]->setRecord(player);
			player_actors[player.ID]->Destroy();
			player_deadcount++;
		}
		return true;
	}
	else
	{
		return false;
	}

}

void ABattleGameModeBase::Finish()
{
	audio->Stop();
	UGameplayStatics::PlaySound2D(GetWorld(), Sound_Finish);
	battle_log_w->Update("The enemies are defeated.");
	FString str_exp = FString::Printf(TEXT("%d"), sum_exp);
	FString s = "Each party member receives " + str_exp + " experience points!";
	battle_log_w->Dead_Finish(s);
	enemy_actors.Empty();
	player_actors.Empty();
	if (sum_exp >= instance->player_infos.Find(0)->NEXTLv_EXP)
	{
		state = Battle_State::Nop;
		TFunction<void(void)> Func = [this]() {
			state = Battle_State::LevelUp;
			instance->player_infos.Find(0)->Lv += 1;
		};
		FTimerHandle Handle;
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		GetWorld()->GetTimerManager().SetTimer(Handle, (TFunction<void(void)>&&)Func, 2.0f, false);
	}
	else
	{
		state = Battle_State::Nop;
		OpenField();
	}
}

void ABattleGameModeBase::Nop()
{
	FString str_exp = FString::Printf(TEXT("%d"), sum_exp);
	FString s = "Each party member receives " + str_exp + " experience points!";
	battle_log_w->Dead_Finish(s);
	//UKismetSystemLibrary::PrintString(this, "Nop", true, true, FColor::Yellow, 3.f, TEXT("None"));

}

void ABattleGameModeBase::setState(Battle_State s)
{
	state = s;
}

void ABattleGameModeBase::Animation()
{
	this->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	/* Nopと同じ */
	//UKismetSystemLibrary::PrintString(this, "Animation", true, true, FColor::Yellow, 3.f, TEXT("None"));
}
void ABattleGameModeBase::AnimationFinished()
{

	//UKismetSystemLibrary::PrintString(this, "AnimationFinished", true, true, FColor::Red, 3.f, TEXT("None"));
	if (enemy_deadcount == enemy_num)
	{
		//UKismetSystemLibrary::PrintString(this, "Finish", true, true, FColor::Black, 3.f, TEXT("None"));
		TFunction<void(void)> Func = [this]() {
			setState(Battle_State::Finish);
		};
		FTimerHandle Handle;
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		GetWorld()->GetTimerManager().SetTimer(Handle, (TFunction<void(void)>&&)Func, 1.f, false);
		setState(Battle_State::Wait);
	}
	else if (player_order.IsEmpty() && enemy_order.IsEmpty())
	{
		//UKismetSystemLibrary::PrintString(this, "Init", true, true, FColor::Black, 3.f, TEXT("None"));
		TFunction<void(void)> Func = [this]() {
			setState(Battle_State::Init);
		};
		FTimerHandle Handle;
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		GetWorld()->GetTimerManager().SetTimer(Handle, (TFunction<void(void)>&&)Func, 1.f, false);
		setState(Battle_State::Wait);
	}
	else 
	{
		//UKismetSystemLibrary::PrintString(this, "Attack", true, true, FColor::Black, 3.f, TEXT("None"));
		TFunction<void(void)> Func = [this]() {
			setState(Battle_State::Attack);
		};
		FTimerHandle Handle;
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		GetWorld()->GetTimerManager().SetTimer(Handle, (TFunction<void(void)>&&)Func, 0.8f, false);
		setState(Battle_State::Wait);
	}
}

void ABattleGameModeBase::LevelUp()
{
	UGameplayStatics::PlaySound2D(GetWorld(), Sound_LevelUp);
	battle_log_w->Collapsed();
	FString str_Lv = FString::Printf(TEXT("%d"), instance->player_infos.Find(0)->Lv);
	FString s = instance->player_infos.Find(0)->NAME.ToString() + "'s level increases to Lv " + str_Lv + "!";
	battle_log_w->Update(s);
	OpenField();
	state = Battle_State::Wait;
}

void ABattleGameModeBase::OpenField()
{
	TFunction<void(void)> Func = [this]() {
		UGameplayStatics::OpenLevel(GetWorld(), "Field", true);
	};
	FTimerHandle Handle;
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	GetWorld()->GetTimerManager().SetTimer(Handle, (TFunction<void(void)>&&)Func, 4.0f, false);
}

void ABattleGameModeBase::Wait()
{

}


