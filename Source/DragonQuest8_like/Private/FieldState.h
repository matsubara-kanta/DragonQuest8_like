// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FieldState.generated.h"

#define INTERVAL 60*3
#define MAXRANGE 9
#define MINRANGE 0

UCLASS()
class AFieldState : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFieldState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int count;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
