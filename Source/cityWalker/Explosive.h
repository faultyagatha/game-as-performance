// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "Explosive.generated.h"

/**
 * 
 */
UCLASS()
class CITYWALKER_API AExplosive : public APickUp
{
	GENERATED_BODY()
    
public:
    AExplosive();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float Damage;
    
    
    /** overridden, used to cause damage */
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

