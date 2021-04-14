// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlataform.h"

// Sets default values
AFloatingPlataform::AFloatingPlataform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = MeshComponent;

	StartPoint = FVector(0.f);
	EndPoint = FVector(0.f);

	InterpSpeed = 1.f;

	bInterping = false;


}

// Called when the game starts or when spawned
void AFloatingPlataform::BeginPlay()
{
	Super::BeginPlay();

	StartPoint = GetActorLocation();
	EndPoint += StartPoint;

	GetWorldTimerManager().SetTimer(InterpTimeHandler, this,
		&AFloatingPlataform::ToggleInterping, InterpTime);

}

// Called every frame
void AFloatingPlataform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bInterping)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector Interp = FMath::VInterpTo(CurrentLocation, EndPoint, DeltaTime, InterpSpeed);

		SetActorLocation(Interp);

		if ( (GetActorLocation() - EndPoint).Size() < 1.f)
		{
			ToggleInterping();

			GetWorldTimerManager().SetTimer(InterpTimeHandler, this,
				&AFloatingPlataform::ToggleInterping, InterpTime);
			SwapVectors(StartPoint, EndPoint);
		}
	}

}

void AFloatingPlataform::ToggleInterping()
{
	bInterping = !bInterping;
}

void AFloatingPlataform::SwapVectors(FVector& VecOne, FVector& VecTwo)
{
	FVector Temp = VecOne;
	VecOne = VecTwo;
	VecTwo = Temp;
	
}

