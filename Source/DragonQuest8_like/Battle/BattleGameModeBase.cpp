// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGameModeBase.h"
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
	for (auto& info : Party_Infos)
	{
		delete info;
	}
}

// Called when the game starts or when spawned
void ABattleGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SetupInput();

	FString path = "/Script/UMGEditor.WidgetBlueprint'/Game/DragonQuest8_like/Scenes/Battle/Battle_First_W.Battle_First_W'";
	TSubclassOf<class UUserWidget> WidgetClass;
	UBlueprint* bp = LoadObject<UBlueprint>(NULL, *path);
	ensure(bp);
	if (bp != nullptr)
	{
		WidgetClass = bp->GeneratedClass;
	}

	Battle_First_w = CreateWidget<UBattle_First_Widget>(GetWorld(), WidgetClass);
	ensure(Battle_First_w);
	if (Battle_First_w) {
		Battle_First_w->AddToViewport();
	}

	switcher = Battle_First_w->getSwitcher();
	ensure(switcher);


	FString path2 = "/Script/UMGEditor.WidgetBlueprint'/Game/DragonQuest8_like/Scenes/Battle/Battle_Command_W.Battle_Command_W'";
	TSubclassOf<class UUserWidget> WidgetClass2;
	UBlueprint* bp2 = LoadObject<UBlueprint>(NULL, *path2);
	ensure(bp2);
	if (bp2 != nullptr)
	{
		WidgetClass2 = bp2->GeneratedClass;
	}

	battle_command_w = CreateWidget<UBattle_Command_Widget>(GetWorld(), WidgetClass2);
	ensure(battle_command_w);
	if (battle_command_w != nullptr)
	{
		switcher->AddChild(battle_command_w);
	}



	// ここはゲームを始めた段階でステータスを初期化、それ以降はステータスを保存しておいてそれを使うように
	// forループ回して値を初期化したい
	Party_Infos.Add(new BattleCharacter(15, 21, 8, 10, 10, 10, 10, BattleCharacter::Chara_State::ALIVE, 0, "エイト"));
	Party_Infos.Add(new BattleCharacter(20, 5, 9, 20, 20, 20, 20, BattleCharacter::Chara_State::ALIVE, 1, "ヤンガス"));

	Battle_First_w->Init(Party_Infos);
}

// Called every frame
void ABattleGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (state)
	{
	case Battle_State::Command_Wait:
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
	UE_LOG(LogTemp, Warning, TEXT("PressedB"));

}

void ABattleGameModeBase::PressedD()
{
	for (int32 index = 0; index != Party_Infos.Num(); ++index)
	{
		UKismetSystemLibrary::PrintString(this, Party_Infos[index]->printAll(), true, true, FColor::Cyan, 10.f, TEXT("None"));
	}

	UE_LOG(LogTemp, Warning, TEXT("PressedD"));
}

void ABattleGameModeBase::SetupInput()
{
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	InputComponent->BindKey(EKeys::B, IE_Pressed, this, &ABattleGameModeBase::PressedB);
	InputComponent->BindKey(EKeys::D, IE_Pressed, this, &ABattleGameModeBase::PressedD);

}


void ABattleGameModeBase::Command_Wait()
{
	//EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	// コマンドがいくつ入力されたか取得
	//state = Battle_State::Attack;
}

void ABattleGameModeBase::Attack()
{
	Battle_First_w->Update(Party_Infos);
}

void ABattleGameModeBase::Escape()
{
	//DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}



