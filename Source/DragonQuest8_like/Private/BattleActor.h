// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "BattleActor.generated.h"

#define DURATION 2.0f


UCLASS()
class ABattleActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABattleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SetupInput();
	void PressedSpaceBar();
	void PrintStructure(const FEnemy& enemy);
	void PressedActionPrintStructure();

	TArray<FEnemy> Enemy_Infos = { {10,10,10,10,10,10,"Corpse_Melee"},
	{20,20,20,20,20,20,"Corpse_Sword"},{30,30,30,30,30,30,"Large_Sword3"} };
};
