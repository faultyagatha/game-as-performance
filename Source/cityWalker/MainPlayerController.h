// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CITYWALKER_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
    
public:
    
    AMainPlayerController();
    
    /** reference to the UMG asset in the editor */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
    TSubclassOf<class UUserWidget> HudOverlayAsset;
    
    /** holds the widget after creating it */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
    UUserWidget* HudOverlay;
    
protected:
    virtual void BeginPlay() override;
    
	
};
