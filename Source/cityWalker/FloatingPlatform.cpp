// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
    
    StartPoint = FVector(0.f);
    EndPoint = FVector(0.f);
    InterpSpeed = 4.f;
    InterpTime = 1.f;
    bInterping = false;

}

void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();
    StartPoint = GetActorLocation();
    //EndPoint is initially in local space
    EndPoint += StartPoint;
    
    GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterping, InterpTime);
    Distance = (EndPoint - StartPoint).Size();
	
}

void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if(bInterping)
    {
        FVector CurrentLocation = GetActorLocation();
        //interpolate between two locations of the platform
        FVector Interp = FMath::VInterpTo(CurrentLocation, EndPoint, DeltaTime, InterpSpeed);
        SetActorLocation(Interp);
        float DistanceTravelled = (GetActorLocation() - StartPoint).Size();
        if(Distance - DistanceTravelled <= 1.f)
        {
            ToggleInterping();
            GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterping, InterpTime);
            //swap the direction of the platform so that it will float back and forth
            SwapVectors(StartPoint, EndPoint);
        }
    }
}

void AFloatingPlatform::ToggleInterping()
{
    bInterping = !bInterping;
}

void AFloatingPlatform::SwapVectors(FVector& VecOne, FVector& VecTwo)
{
    FVector Temp = VecOne;
    VecOne = VecTwo;
    VecTwo = Temp;
}

