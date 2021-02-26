// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "MainCharacter.h"

AItem::AItem()
{
    PickupCount = 1;
}

void AItem::OnOverlapBegin(
                           UPrimitiveComponent* OverlappedComp,
                           AActor* OtherActor,
                           UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex,
                           bool bFromSweep,
                           const FHitResult& SweepResult)
{
    if(OtherActor)
    {
        //returns null if MainChar is not of type AMainCharacter
        AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
        if(MainChar)
        {
            MainChar->IncrementPickups(PickupCount);
            MainChar->PickupLocations.Add(GetActorLocation()); //add the pickup to the locations TArray
            Destroy(); //destroy the item after picking it up
        }
    }
}

void AItem::OnOverlapEnd(
                          UPrimitiveComponent* OverlappedComp,
                          AActor* OtherActor,
                          UPrimitiveComponent* OtherComp,
                          int32 OtherBodyIndex)
{
    
}
