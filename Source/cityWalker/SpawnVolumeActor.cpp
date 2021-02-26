// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolumeActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "FloaterPawn.h"

ASpawnVolumeActor::ASpawnVolumeActor()
{
	PrimaryActorTick.bCanEverTick = true;
    
    SpawnedBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnedBox"));

}

void ASpawnVolumeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpawnVolumeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolumeActor::GetSpawedPoint()
{
    FVector Extent = SpawnedBox->GetScaledBoxExtent();
    FVector Origin = SpawnedBox->GetComponentLocation();
    //calculate a random point within the bounding box using the first vector as an origin and the second as the box extents
    FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
    return Point;
}

//comes from BlueprintNativeEvent macro
void ASpawnVolumeActor::SpawnPawn_Implementation(UClass* ToSpawn, const FVector& Location)
{
    if(ToSpawn)
    {
        UWorld* World = GetWorld();
        FActorSpawnParameters SpawnParams;
        if(World)
        {
            AFloaterPawn* FloaterPawn = World->SpawnActor<AFloaterPawn>(ToSpawn, Location, FRotator(0.f), SpawnParams);
        }
    }
}

