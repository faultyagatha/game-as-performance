// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CITYWALKER_API UMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
    
public:
    
    /** "beginPlay for animations" */
    virtual void NativeInitializeAnimation() override;
    
    /** custom function that update animation every frame */
    UFUNCTION(BlueprintCallable, Category = "Animation")
    void UpdateAnimationProperties();
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float MovementSpeed;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    bool bIsInAir;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    class APawn* Pawn;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    class AMainCharacter* MainChar;
	
};
