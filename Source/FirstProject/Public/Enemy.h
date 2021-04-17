// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "AIController.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Sound/SoundCue.h"

#include "Enemy.generated.h"

class AMain;
UENUM(BlueprintType)
enum class EEnemyMovementStatus:uint8
{
	EEMS_Idle			UMETA(DisplayName = "Idle"),
	EEMS_MoveToTarget	UMETA(DisplayName = "MoveToTarget"),
	EEMS_Attacking		UMETA(DisplayName = "Attacking"),

	EEMS_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class FIRSTPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	EEnemyMovementStatus EnemyMovementStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundCue* HitSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundCue* SwingSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	USphereComponent* AggroRangeSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	USphereComponent* AttackRangeSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	AAIController* AIController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	bool bOverlappingCombatSphere;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	AMain* CombatTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	UBoxComponent* CombatCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* CombatMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bAttacking;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetEnemyMovementStatus(const EEnemyMovementStatus Status) { EnemyMovementStatus = Status; }

	#pragma region OverlapEvents
	UFUNCTION()
	virtual void AggroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void AggroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void AttackSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void AttackSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult & SweepResult);

	UFUNCTION()
    void CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	#pragma endregion

	UFUNCTION(BlueprintCallable)
	void MoveToTarget(AMain* Target);

	UFUNCTION(BlueprintCallable)
	void ActivateCollision();
	
	UFUNCTION(BlueprintCallable)
    void DeactivateCollision();

	void Attack();
	
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
};
