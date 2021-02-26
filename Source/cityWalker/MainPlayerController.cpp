// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"

AMainPlayerController::AMainPlayerController()
{
    
}

void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if(HudOverlayAsset)
    {
        HudOverlay = CreateWidget<UUserWidget>(this, HudOverlayAsset);
    }
    HudOverlay->AddToViewport();
    HudOverlay->SetVisibility(ESlateVisibility::Visible);
}
