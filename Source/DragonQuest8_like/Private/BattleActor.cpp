// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ABattleActor::ABattleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleActor::BeginPlay()
{
	Super::BeginPlay();
	SetupInput();
	Battle_First_w = CreateWidget<UBattle_First_Widget>(GetWorld(), WBP_Battle_First);
	ensure(Battle_First_w);
	if (Battle_First_w) {
		Battle_First_w->AddToViewport();
	}

}

void ABattleActor::SetupInput()
{
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	InputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &ABattleActor::PressedSpaceBar);
	InputComponent->BindKey(EKeys::Enter, IE_Pressed, this, &ABattleActor::PressedActionPrintStructure);

}

void ABattleActor::PressedSpaceBar() {
	UGameplayStatics::OpenLevel(GetWorld(), "Field");
}

// Called every frame
void ABattleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABattleActor::PrintStructure(const FEnemy& enemy)
{
	UKismetSystemLibrary::PrintString(this, enemy.Name + " " + FString::FromInt(enemy.HP) + " " + FString::FromInt(enemy.Attack) + " " + FString::FromInt(enemy.Defense) + " " + FString::FromInt(enemy.M_Attack) + " " + FString::FromInt(enemy.M_Defense) + " " + FString::FromInt(enemy.Speed), true, true, FColor::Cyan, DURATION, TEXT("None"));
}

void ABattleActor::PressedActionPrintStructure() {
	for (int32 Index = 0; Index < Enemy_Infos.Num(); ++Index)
		PrintStructure(Enemy_Infos[Index]);
}
