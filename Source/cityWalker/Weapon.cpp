// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MainCharacter.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AWeapon::AWeapon()
{
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMesh->SetupAttachment(GetRootComponent());
    bWeaponParticles = false;
    WeaponState = EWeaponState::EWS_Pickup;
}

void AWeapon::OnOverlapBegin(
                    UPrimitiveComponent* OverlappedComp,
                    AActor* OtherActor,
                    UPrimitiveComponent* OtherComp,
                    int32 OtherBodyIndex,
                    bool bFromSweep,
                    const FHitResult& SweepResult)
{
    Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    if((WeaponState == EWeaponState::EWS_Pickup) && OtherActor)
    {
        AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
        if(MainCharacter)
        {
//            Equip(MainCharacter); //if we want to give no choice - equip the weapon automatically on overlap
            MainCharacter->SetActiveOverlapingPickup(this);
        }
    }
}
    

void AWeapon::OnOverlapEnd(
                          UPrimitiveComponent* OverlappedComp,
                          AActor* OtherActor,
                          UPrimitiveComponent* OtherComp,
                          int32 OtherBodyIndex)
{
    Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
    if(OtherActor)
    {
        AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
        if(MainCharacter)
        {
            MainCharacter->SetActiveOverlapingPickup(nullptr);
        }
    }
}

void AWeapon::Equip(AMainCharacter* Character)
{
    if(Character)
    {
        SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
        SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
        SkeletalMesh->SetSimulatePhysics(false);
        
        const USkeletalMeshSocket* RightHandSocket = Character->GetMesh()->GetSocketByName("RightHandSocket");
        if(RightHandSocket)
        {
            RightHandSocket->AttachActor(this, Character->GetMesh());
            bIsRotating = false;
            Character->SetEquipedWeapon(this);
            Character->SetActiveOverlapingPickup(nullptr);
        }
        if(OnEquipSound) //TODO: attach sounds in blueprint
        {
            UGameplayStatics::PlaySound2D(this, OnEquipSound);
        }
        if(!bWeaponParticles)
        {
            IdleParticles->Deactivate();
        }
    }
}

