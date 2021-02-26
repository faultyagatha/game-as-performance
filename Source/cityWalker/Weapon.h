// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "Weapon.generated.h"

class USkeletalMeshComponent;
class AMainCharacter;
class USoundCue;

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
    EWS_Pickup   UMETA(DisplayName = "Pickup"),
    EWS_Equipped UMETA(DisplayName = "Equipped"),
    EWS_MAX      UMETA(DisplayName = "DefaultMax")
};

/**
 * 
 */
UCLASS()
class CITYWALKER_API AWeapon : public APickUp
{
	GENERATED_BODY()

public:
    AWeapon();
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickups")
    EWeaponState WeaponState;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh")
    USkeletalMeshComponent* SkeletalMesh;
    
    /** sound playing on equiping the player */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundCue* OnEquipSound;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickupParticles")
    bool bWeaponParticles;
    
    /** inherited from Pickup class */
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
    
    void Equip(AMainCharacter* Character);
    
    FORCEINLINE void SetWeaponState(EWeaponState State) { WeaponState = State; }
    FORCEINLINE EWeaponState GetWeaponState() { return WeaponState; }
    
};
