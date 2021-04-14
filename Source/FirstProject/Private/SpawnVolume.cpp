// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawning Box"));

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetSpawnPoint()
{
	const FVector Extent = SpawningBox->GetScaledBoxExtent();
	const FVector Origin = SpawningBox->GetComponentLocation();

	const FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);

	return RandomPoint;
}

void ASpawnVolume::SpawnPawn_Implementation(UClass* Pawn, const FVector& Location)
{
	if (Pawn)
	{
		UWorld* World = GetWorld();
		const FActorSpawnParameters ActorSpawnParameters;
		if (World)
		{
			ACritter* Critter = World->SpawnActor<ACritter>(Pawn, Location, FRotator(0.f), ActorSpawnParameters);
		}
	}
}

