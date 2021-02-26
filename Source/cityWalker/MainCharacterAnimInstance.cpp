// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "MainCharacter.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
    if(Pawn == nullptr)
    {
        Pawn = TryGetPawnOwner(); //return the pawn in animation instance
        if(Pawn)
        {
            MainChar = Cast<AMainCharacter>(Pawn);
        }
    }
    
}

void UMainCharacterAnimInstance::UpdateAnimationProperties()
{
    if(Pawn == nullptr)
    {
        Pawn = TryGetPawnOwner();
    }
    if(Pawn)
    {
        FVector Speed = Pawn->GetVelocity();
        FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
        MovementSpeed = LateralSpeed.Size();
        
        bIsInAir = Pawn->GetMovementComponent()->IsFalling();
        
        if(MainChar == nullptr)
        {
            MainChar = Cast<AMainCharacter>(Pawn);
        }
    }
}
