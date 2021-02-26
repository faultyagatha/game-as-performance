// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class UParticleSystem;
class USoundCue;

UCLASS()
class CITYWALKER_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:
	APickUp();
    
    /** base shape collision*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickups | Collision")
    USphereComponent* CollisionVolume;
    
    /** base shape mesh*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickups | Mesh")
    UStaticMeshComponent* MeshComponent;
    
    /** default idle partices */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups | Particles")
    UParticleSystemComponent* IdleParticles;
    
    /** emited on overlap */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups | Particles")
    UParticleSystem* OverlapParticles;
    
    /** played on overlap */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups | Sound")
    USoundCue* OverlapSound;
    
    /** rotations */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups | Properties")
    bool bIsRotating;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups | Properties")
    float RotationRate;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
    
    /** OnOverlapBegin and End will be used by the child classes for different item pickups */
    UFUNCTION()
    virtual void OnOverlapBegin(
                        UPrimitiveComponent* OverlappedComp,
                        AActor* OtherActor,
                        UPrimitiveComponent* OtherComp,
                        int32 OtherBodyIndex,
                        bool bFromSweep,
                        const FHitResult& SweepResult);
    
    UFUNCTION()
    virtual void OnOverlapEnd(
                      UPrimitiveComponent* OverlappedComp,
                      AActor* OtherActor,
                      UPrimitiveComponent* OtherComp,
                      int32 OtherBodyIndex);

};
