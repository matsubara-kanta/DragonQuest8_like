// Copyright Epic Games, Inc. All Rights Reserved.

#include "DragonQuest8_likeGameMode.h"
#include "DragonQuest8_likeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADragonQuest8_likeGameMode::ADragonQuest8_likeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
