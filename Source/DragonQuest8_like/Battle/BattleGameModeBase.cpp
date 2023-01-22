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

	UDQ8GameInstance* instance = UDQ8GameInstance::GetInstance();
	ensure(instance != nullptr);
	if (instance)
	{
		Battle_First_w->Init(instance->player_infos);
	}
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
	UE_LOG(LogTemp, Warning, TEXT("PressedB"));
	battle_command_w->setkougekiButton(true);
}

void ABattleGameModeBase::PressedD()
{
	for (int32 index = 0; index != player_infos.Num(); ++index)
	{
		UKismetSystemLibrary::PrintString(this, "HP:	 " + FString::FromInt(player_infos[index].HP) + "            MP:  " + FString::FromInt(player_infos[index].MP) + "            Lv:  " + FString::FromInt(player_infos[index].Lv) + "           ATK:  " + FString::FromInt(player_infos[index].ATK) + "         DEF:  " + FString::FromInt(player_infos[index].DEF) + "           INT:  " + FString::FromInt(player_infos[index].INT) + "         SPD:  " + FString::FromInt(player_infos[index].SPD) + "         STATE:  " + FString::FromInt(player_infos[index].STATE) + "           ID:  " + FString::FromInt(player_infos[index].ID) + "          NAME:  " + player_infos[index].NAME.ToString(), true, true, FColor::Cyan, 10.f, TEXT("None"));
	}

	UE_LOG(LogTemp, Warning, TEXT("PressedD"));
}

void ABattleGameModeBase::SetupInput()
{
	//FInputModeGameAndUI InputMode;
	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(InputMode);
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	InputComponent->BindKey(EKeys::B, IE_Pressed, this, &ABattleGameModeBase::PressedB);
	InputComponent->BindKey(EKeys::D, IE_Pressed, this, &ABattleGameModeBase::PressedD);

}


void ABattleGameModeBase::Command_Wait()
{
	//EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	// ƒRƒ}ƒ“ƒh‚ª‚¢‚­‚Â“ü—Í‚³‚ê‚½‚©Žæ“¾
	//state = Battle_State::Attack;
	Battle_First_w->setNigeruButton(true);
}

void ABattleGameModeBase::Attack()
{
	Battle_First_w->Update(player_infos);
}

void ABattleGameModeBase::Escape()
{
	//DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}



