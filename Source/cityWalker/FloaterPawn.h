// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FloaterPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;

UCLASS()
class CITYWALKER_API AFloaterPawn : public APawn
{
	GENERATED_BODY()

public:
	AFloaterPawn();
    
    UPROPERTY(EditAnywhere, Category = "PawnMesh")
    UStaticMeshComponent* MeshComponent;
    
    UPROPERTY(EditAnywhere, Category = "PawnCamera")
    UCameraComponent* Camera;
    
    UPROPERTY(EditAnywhere, Category = "PawnMovement")
    float MaxSpeed;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
private:
    /** needed for input binding BindAxis */
    void MoveForward(float Value);
    void MoveRight(float Value);
    
    FVector CurrentVelocity;

};
