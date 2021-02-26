// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class CITYWALKER_API AItem : public APickUp
{
	GENERATED_BODY()
    
public:
    AItem();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups")
    int32 PickupCount;
    
    /** OnOverlapBegin and End used for different item pickups */
    virtual void OnOverlapBegin(
                                UPrimitiveComponent* OverlappedComp,
                                AActor* OtherActor,
                                UPrimitiveComponent* OtherComp,
                                int32 OtherBodyIndex,
                                bool bFromSweep,
                                const FHitResult& SweepResult) override;
    
    virtual void OnOverlapEnd(
                              UPrimitiveComponent* OverlappedComp,
                              AActor* OtherActor,
                              UPrimitiveComponent* OtherComp,
                              int32 OtherBodyIndex) override;
	
};
