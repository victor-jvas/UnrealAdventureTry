// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			Enemy = Cast<AEnemy>(Pawn);
		}
	}
}

void UEnemyAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			Enemy = Cast<AEnemy>(Pawn);
		}
	}

	if (Pawn)
	{
		const FVector Speed = Pawn->GetVelocity();
		const FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();
	}
}

