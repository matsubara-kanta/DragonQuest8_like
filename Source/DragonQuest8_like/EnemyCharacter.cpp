// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::setRecord(FEnemyDataAssetRecord record)
{
	enemy_record = record;
}

FEnemyDataAssetRecord AEnemyCharacter::getRecord()
{
	return enemy_record;
}

void AEnemyCharacter::searchRecord(FText str)
{
	FString s = str.ToString();
	UDQ8GameInstance* instance = UDQ8GameInstance::GetInstance();
	ensure(instance != nullptr);

	for (FEnemyDataAssetRecord record : instance->enemy_infos)
	{
		if (s.StartsWith(record.NAME.ToString()))
		{
			//UE_LOG(LogTemp, Warning, TEXT("record pass"));
			setRecord(record);
			//UKismetSystemLibrary::PrintText(this,enemy_record.NAME);
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("no record found"));
	return;
}

void AEnemyCharacter::setID(int32 id)
{
	enemy_record.ID = id;
}

void AEnemyCharacter::Print_All_Infos()
{
	UKismetSystemLibrary::PrintString(this, "HP:	 " + FString::FromInt(enemy_record.HP) + "            MP:  " + FString::FromInt(enemy_record.MP) + "            Lv:  " + FString::FromInt(enemy_record.Lv) + "           ATK:  " + FString::FromInt(enemy_record.ATK) + "         DEF:  " + FString::FromInt(enemy_record.DEF) + "           INT:  " + FString::FromInt(enemy_record.INT) + "         SPD:  " + FString::FromInt(enemy_record.SPD) + "         STATE:  " + FString::FromInt(enemy_record.STATE) + "           ID:  " + FString::FromInt(enemy_record.ID) + "          NAME:  " + enemy_record.NAME.ToString(), true, true, FColor::Cyan, 10.f, TEXT("None"));
}