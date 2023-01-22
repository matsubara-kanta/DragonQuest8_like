// Fill out your copyright notice in the Description page of Project Settings.


#include "DQ8GameInstance.h"
#include "Engine/Engine.h"

UDQ8GameInstance* UDQ8GameInstance::GetInstance()
{
    UDQ8GameInstance* instance = nullptr;

    if (GEngine)
    {
        FWorldContext* context = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
        instance = Cast<UDQ8GameInstance>(context->OwningGameInstance);
    }

    return instance;
}


void UDQ8GameInstance::DisplayDebugMessage(FString message)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, message);
    }
}
