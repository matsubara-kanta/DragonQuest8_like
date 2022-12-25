// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAL/PlatformProcess.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values
AFieldState::AFieldState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFieldState::BeginPlay()
{
	Super::BeginPlay();
	count = 0;
}

// Called every frame
void AFieldState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (count > INTERVAL) {
		UKismetSystemLibrary::PrintString(this, "INTERVAL", true, true, FColor::Cyan, 2.f, TEXT("None"));
		int random = FMath::RandRange(MINRANGE, MAXRANGE);
		if (random % 7 == 0) {
			UGameplayStatics::OpenLevel(GetWorld(), "Battle");
		}
		count = 0;
	}
		
	count++;


	
}

