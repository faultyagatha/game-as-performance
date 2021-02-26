// Fill out your copyright notice in the Description page of Project Settings.


#include "FloaterPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

AFloaterPawn::AFloaterPawn()
{
	PrimaryActorTick.bCanEverTick = true;
    
    //pawn has already root component by default (inherits from actor)
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(GetRootComponent()); //attach mesh to the root
    
    //we need the camera to move the pawn around in the world
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(GetRootComponent()); //attach mesh to the root
    Camera->SetRelativeLocation(FVector(-300.f, 0.f, 300.f));
    Camera->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
    
    //AutoPossessPlayer = EAutoReceiveInput::Player0;
    
    CurrentVelocity = FVector(0.f);
    MaxSpeed = 100.f;

}

void AFloaterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFloaterPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
    SetActorLocation(NewLocation);

}

void AFloaterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFloaterPawn::MoveForward); //funky way of calling a function
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFloaterPawn::MoveRight);
}

void AFloaterPawn::MoveForward(float Value) {
    CurrentVelocity.X = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
}

void AFloaterPawn::MoveRight(float Value) {
    CurrentVelocity.Y = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
}

