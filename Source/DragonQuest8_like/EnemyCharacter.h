// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyDataAsset.h"
#include "DQ8GameInstance.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DRAGONQUEST8_LIKE_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	FEnemyDataAssetRecord getRecord();
	void setID(int32 id);
	void Print_All_Infos();

protected:
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void searchRecord(int32 index);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FEnemyDataAssetRecord enemy_record;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void setRecord(FEnemyDataAssetRecord* record);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
