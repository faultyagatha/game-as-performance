// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class CITYWALKER_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();
    
    /** triggable overlap volume */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FloorSwitch")
    UBoxComponent* TriggerBox;
    
    /** switch for the character step on */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FloorSwitch")
    UStaticMeshComponent* FloorSwitch;
    
    /** door to move when a floor switch is stepped on */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FloorSwitch")
    UStaticMeshComponent* Door;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FloorSwitch")
    FVector InitialDoorLocation;
    
    UPROPERTY(BlueprintReadWrite, Category = "FloorSwitch")
    FVector InitialFloorSwitchLocation;
    
    /** time needed for the timer that controlles the door switch */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloorSwitch")
    float SwitchTime;
    
    FTimerHandle SwitchHandle;
    
    /** is the character is already on the switch platform? */
    bool bCharacterOnSwitch;
    
    
    

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
    
    UFUNCTION()
    void OnOverlapBegin(
                        UPrimitiveComponent* OverlappedComp,
                        AActor* OtherActor,
                        UPrimitiveComponent* OtherComp,
                        int32 OtherBodyIndex,
                        bool bFromSweep,
                        const FHitResult& SweepResult);
    
    UFUNCTION()
    void OnOverlapEnd(
                      UPrimitiveComponent* OverlappedComp,
                      AActor* OtherActor,
                      UPrimitiveComponent* OtherComp,
                      int32 OtherBodyIndex);
    
    /** is implemented in blueprint */
    UFUNCTION(BlueprintImplementableEvent, Category = "FloorSwitch")
    void RaiseDoor();
    
    /** is implemented in blueprint */
    UFUNCTION(BlueprintImplementableEvent, Category = "FloorSwitch")
    void LowerDoor();
    
    /** is implemented in blueprint */
    UFUNCTION(BlueprintImplementableEvent, Category = "FloorSwitch")
    void RaiseFloorSwitch();
    
    /** is implemented in blueprint */
    UFUNCTION(BlueprintImplementableEvent, Category = "FloorSwitch")
    void LowerFloorSwitch();
    
    UFUNCTION(BlueprintCallable, Category = "FloorSwitch")
    void UpdateDoorLocation(float Z);
    
    UFUNCTION(BlueprintCallable, Category = "FloorSwitch")
    void UpdateFloorSwitchLocation(float Z);
    
    void CloseDoor();

};
