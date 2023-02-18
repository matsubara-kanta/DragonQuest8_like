// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EnemyDataAsset.h"
#include "DQ8GameInstance.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DRAGONQUEST8_LIKE_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;


public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void setRecord(FEnemyDataAssetRecord record);

	UFUNCTION(BlueprintImplementableEvent, Category = "MyFunc")
		void Damaged();

	UFUNCTION(BlueprintImplementableEvent, Category = "MyFunc")
		void Attack();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }



	FEnemyDataAssetRecord getRecord();
	void setID(int32 id);
	void Print_All_Infos();

protected:
	UFUNCTION(Blueprintcallable, Category = "Myfunc")
		void searchRecord(int32 index);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FEnemyDataAssetRecord enemy_record;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
