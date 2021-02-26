// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
    RootComponent = CollisionVolume;
    CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnOverlapBegin);
    CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &APickUp::OnOverlapEnd);
    
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    MeshComponent->SetupAttachment(GetRootComponent());
    
    IdleParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IdleParticles"));
    IdleParticles->SetupAttachment(GetRootComponent());
    
    bIsRotating = false;
    RotationRate = 45.f;

}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(bIsRotating)
    {
        FRotator Rotation = GetActorRotation();
        Rotation.Yaw += DeltaTime * RotationRate;
        SetActorRotation(Rotation);
    }

}

void APickUp::OnOverlapBegin(
                    UPrimitiveComponent* OverlappedComp,
                    AActor* OtherActor,
                    UPrimitiveComponent* OtherComp,
                    int32 OtherBodyIndex,
                    bool bFromSweep,
                    const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("BeginOverlap"));
    if(OverlapParticles)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticles, GetActorLocation(), FRotator(0.f), true);
    }
    if(OverlapSound)
    {
        UGameplayStatics::PlaySound2D(this, OverlapSound);
    }
}

void APickUp::OnOverlapEnd(
                          UPrimitiveComponent* OverlappedComp,
                          AActor* OtherActor,
                          UPrimitiveComponent* OtherComp,
                          int32 OtherBodyIndex)
{
    UE_LOG(LogTemp, Warning, TEXT("EndOverlap"));
}

