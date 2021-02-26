// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosive.h"
#include "MainCharacter.h"

AExplosive::AExplosive()
{
    Damage = 15.f;
}

void AExplosive::OnOverlapBegin(
                            UPrimitiveComponent* OverlappedComp,
                            AActor* OtherActor,
                            UPrimitiveComponent* OtherComp,
                            int32 OtherBodyIndex,
                            bool bFromSweep,
                            const FHitResult& SweepResult)
{
    Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp,OtherBodyIndex, bFromSweep, SweepResult);
    UE_LOG(LogTemp, Warning, TEXT("BeginOverlap"));
    if(OtherActor)
    {
        //returns null if MainChar is not of type AMainCharacter
        AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
        if(MainChar)
        {
            MainChar->DecrementHealth(Damage);
            Destroy();
            
        }
    }
}

void AExplosive::OnOverlapEnd(
                          UPrimitiveComponent* OverlappedComp,
                          AActor* OtherActor,
                          UPrimitiveComponent* OtherComp,
                          int32 OtherBodyIndex)
{
    Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp,OtherBodyIndex);
    UE_LOG(LogTemp, Warning, TEXT("EndOverlap"));
}
