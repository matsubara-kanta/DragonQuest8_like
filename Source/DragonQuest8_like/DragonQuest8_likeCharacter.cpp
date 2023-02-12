// Copyright Epic Games, Inc. All Rights Reserved.

#include "DragonQuest8_likeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


//////////////////////////////////////////////////////////////////////////
// ADragonQuest8_likeCharacter

ADragonQuest8_likeCharacter::ADragonQuest8_likeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ADragonQuest8_likeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADragonQuest8_likeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADragonQuest8_likeCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADragonQuest8_likeCharacter::Look);

	}

}

void ADragonQuest8_likeCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ADragonQuest8_likeCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ADragonQuest8_likeCharacter::setRecord(FPlayerDataAssetRecord record)
{
	player_record.ATK = record.ATK;
	player_record.DEF = record.DEF;
	player_record.HP = record.HP;
	player_record.ID = record.ID;
	player_record.INT = record.INT;
	player_record.Lv = record.Lv;
	player_record.MP = record.MP;
	player_record.NAME = record.NAME;
	player_record.SPD = record.SPD;
	player_record.STATE = record.STATE;
	player_record.EXP = record.EXP;
	player_record.NEXTLv_EXP = record.NEXTLv_EXP;
}

FPlayerDataAssetRecord ADragonQuest8_likeCharacter::getRecord()
{
	return player_record;
}

void ADragonQuest8_likeCharacter::searchRecord(int32 index)
{
	UDQ8GameInstance* instance = UDQ8GameInstance::GetInstance();
	ensure(instance != nullptr);
	FPlayerDataAssetRecord* record = instance->player_infos.Find(index);
	setRecord(*record);

	//UE_LOG(LogTemp, Warning, TEXT("no record found"));
	return;
}
void ADragonQuest8_likeCharacter::Print_All_Infos()
{
	UKismetSystemLibrary::PrintString(this, "HP:	 " + FString::FromInt(player_record.HP) + "            MP:  " + FString::FromInt(player_record.MP) + "            Lv:  " + FString::FromInt(player_record.Lv) + "           ATK:  " + FString::FromInt(player_record.ATK) + "         DEF:  " + FString::FromInt(player_record.DEF) + "           INT:  " + FString::FromInt(player_record.INT) + "         SPD:  " + FString::FromInt(player_record.SPD) + "         STATE:  " + FString::FromInt(player_record.STATE) + "           ID:  " + FString::FromInt(player_record.ID) + "          NAME:  " + player_record.NAME.ToString(), true, true, FColor::Cyan, 10.f, TEXT("None"));
}

