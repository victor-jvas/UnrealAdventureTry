// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "Main.generated.h"

class UCameraComponent;

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DIsplayName = "Sprinting"),

	EMS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimun"),
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering UMETA(DisplayName = "ExhaustedRecovering"),

	ESS_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class FIRSTPROJECT_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera);
	float BaseLookUpRate;

	/**
	/*
	/* Player Stats
	/*
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Health;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float MaxStamina;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Stamina;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Coins;

	/** 
	 *
	 * Movement attributes
	 *
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus StaminaStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate;

	/** Minimum Stamina necessary to start sprinting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaThreshold;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float RunningSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bShiftKeyPressed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpRate(float Rate);

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const {return CameraBoom;}
	FORCEINLINE class UCameraComponent* GetFollowCamera() const {return FollowCamera;}

	void Die();

	void IncrementCoins();

	EMovementStatus GetMovementStatus() const;
	void SetMovementStatus(EMovementStatus MovementStatus);

	EStaminaStatus GetStaminaStatus() const;
	void SetStaminaStatus(EStaminaStatus StaminaStatus);

	/** Press down to enable sprinting */
	void ShiftKeyDown();
	/** Release to stop sprinting */
	void ShiftKeyUp();

};
