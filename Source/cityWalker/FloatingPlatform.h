// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingPlatform.generated.h"

class UStaticMeshComponent;

UCLASS()
class CITYWALKER_API AFloatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:
	AFloatingPlatform();
    
    /** */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlatformMesh")
    UStaticMeshComponent* MeshComponent;
    
    /** start and end points of the platform */
    UPROPERTY(EditAnywhere, Category = "PlatformLocation")
    FVector StartPoint;
    
    UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"))
    FVector EndPoint;
    
    UPROPERTY(EditAnywhere, Category = "PlatformSpeed")
    float InterpSpeed;
    
    UPROPERTY(EditAnywhere, Category = "InterpolationTime")
    float InterpTime;
    
    /** timer to handle the platform's back and forth movement */
    FTimerHandle InterpTimer;
    
    UPROPERTY(EditAnywhere, Category = "IsInterpolating")
    bool bInterping;
    
    /** stores a distance between start and end points; is calculated on beginPlay */
    float Distance;
    

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
    void ToggleInterping();
    void SwapVectors(FVector& VecOne, FVector& VecTwo);

};
