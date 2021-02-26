// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolumeActor.generated.h"

class UBoxComponent;

UCLASS()
class CITYWALKER_API ASpawnVolumeActor : public AActor
{
	GENERATED_BODY()
	
public:
	ASpawnVolumeActor();
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawningActors")
    UBoxComponent* SpawnedBox;
    
    /** a template class that will be spawned in the volume box */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpawningActors")
    TSubclassOf<class AFloaterPawn> PawnToSpawn;
    
    /** is only callable from blueprint */
    UFUNCTION(BlueprintPure, Category = "SpawningActors")
    FVector GetSpawedPoint();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
    
    /** UClass is higher in the hierarchy than Actor and Pawn so we could choose */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SpawningActors")
    void SpawnPawn(UClass* ToSpawn, const FVector& Location);
    
    

};
