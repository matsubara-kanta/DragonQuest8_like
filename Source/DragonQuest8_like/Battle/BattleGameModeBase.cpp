// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameModeBase.h"
#include "../DQ8GameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

Battle_State state = Battle_State::Command_Wait;

// Sets default values
ABattleGameModeBase::ABattleGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		state = Battle_State::Command_Wait;
	case Battle_State::Escape:
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
		}
	}
	UKismetSystemLibrary::PrintString(this, "PressedB");
	battle_command_w->setkougekiButton(true);
}

void ABattleGameModeBase::PressedD()
{
	for (int32 index = 0; index < player_infos.Num(); ++index)
	{
		UKismetSystemLibrary::PrintString(this, "HP:	 " + FString::FromInt(player_infos[index].HP) + "            MP:  " + FString::FromInt(player_infos[index].MP) + "            Lv:  " + FString::FromInt(player_infos[index].Lv) + "           ATK:  " + FString::FromInt(player_infos[index].ATK) + "         DEF:  " + FString::FromInt(player_infos[index].DEF) + "           INT:  " + FString::FromInt(player_infos[index].INT) + "         SPD:  " + FString::FromInt(player_infos[index].SPD) + "         STATE:  " + FString::FromInt(player_infos[index].STATE) + "           ID:  " + FString::FromInt(player_infos[index].ID) + "          NAME:  " + player_infos[index].NAME.ToString(), true, true, FColor::Cyan, 10.f, TEXT("None"));
	}

	UKismetSystemLibrary::PrintString(this, "PressedD");
}

void ABattleGameModeBase::PressedK()
{
	if (kill < enemy_actors.Num()) {
		enemy_actors[kill]->Destroy();
		kill++;
	}
	UKismetSystemLibrary::PrintString(this,"PressedK");
}

void ABattleGameModeBase::SetupInput()
{
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	InputComponent->BindKey(EKeys::B, IE_Pressed, this, &ABattleGameModeBase::PressedB);
	InputComponent->BindKey(EKeys::D, IE_Pressed, this, &ABattleGameModeBase::PressedD);
	InputComponent->BindKey(EKeys::K, IE_Pressed, this, &ABattleGameModeBase::PressedK);
}


void ABattleGameModeBase::Command_Wait()
{
	// コマンドがいくつ入力されたか取得
	//state = Battle_State::Attack;
	battle_first_w->setBattle_First_Widget(true);
}

void ABattleGameModeBase::Attack()
{
	battle_first_w->Update(player_infos);
}

void ABattleGameModeBase::Escape()
{
	//DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
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
		battle_first_w->AddToViewport();
	}

}

UBattle_First_Widget* ABattleGameModeBase::getBattleFirstWidget()
{
	return battle_first_w;
}

void ABattleGameModeBase::Init_Player()
{
	/* プレイヤーの初期化 */
	UDQ8GameInstance* instance = UDQ8GameInstance::GetInstance();
	ensure(instance != nullptr);
	if (instance)
	{
		battle_first_w->Init(instance->player_infos);
	}

}
