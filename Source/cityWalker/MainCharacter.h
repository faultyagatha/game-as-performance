// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
    EMS_Normal UMETA(DisplayName = "Normal"),
    EMS_Sprinting UMETA(DisplayName = "Sprinting"),
    EMS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
    ESS_Normal UMETA(DisplayName = "Normal"),
    ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
    ESS_Exhausted UMETA(DisplayName = "Exhausted"),
    ESS_ExhaustedRecovering UMETA(DisplayName = "ExhaustedRecovering"),
    ESS_MAX UMETA(DisplayName = "DefaultMAX")
};

class USpringArmComponent;
class UCameraComponent;
class AWeapon;
class APickUp;

UCLASS()
class CITYWALKER_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
    
    /** position the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* CameraBoom;
    
    /** follow camera functionality */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FollowCamera;
    
    /** turn rates to scale turning functions for the camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    float BaseTurnRate;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    float BaseLookupRate;
    
    /** Player stats */
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerStats")
    float MaxHealth;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
    float Health;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerStats")
    float MaxStamina;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
    float Stamina;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
    int32 Pickups;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
    EMovementStatus MovementStatus;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    float RunningSpeed;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    float SprintingSpeed;
    
    /** right shift enables/disables sprinting */
    bool bShiftKeyDown;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
    EStaminaStatus StaminaStatus;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
    float StaminaDrainRate;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
    float MinSprintStamina;
    
    /** array that stores the locations of pickups */
    TArray<FVector> PickupLocations;
    
    /** weapon */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    AWeapon* EquipedWeapon;
    
    /** any pickup we would like to take with us, e.g. weapon, armor... */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    APickUp* ActiveOverlapingPickup;
    
    bool bLeftMouseButtonDown;


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
     /** called for forward and backward movement inputs */
    void MoveForward(float Value);
    
    /** called for side to side inputs */
    void MoveRight(float Value);
    
    /** called via input to turn at a given rate
     @param Rate is a normalised rate (1.0 is 100% of a desired turn rate)
     */
    void TurnAtRate(float Rate);
    
    /** called via input to look up/down at a given rate
     @param Rate is a normalised rate (1.0 is 100% of a desired look up/down rate)
     */
    void LookupRate(float Rate);
    
    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    
    void DecrementHealth(float Amount);
    
    void IncrementPickups(int32 Amount);
    
    void Die();
    
    /** set movement status and running speed */
    void SetMovementStatus(EMovementStatus Status);
    
    /** pressed down to enable sprinting */
    void ShiftKeyDown();
    
    /** released to stop sprinting */
    void ShiftKeyUp();
    
    /** pickup mechanics */
    void LeftMouseButtonDown();
    
    void LeftMouseButtonUp();
    
    FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }
    
    /** debugging feature: visualise the locations with a debug sphere */
    UFUNCTION(BlueprintCallable)
    void ShowPickupLocations();
    
    void SetEquipedWeapon(AWeapon* WeaponToSet);
    FORCEINLINE AWeapon* GetEquipedWeapon() { return EquipedWeapon; }
    
    FORCEINLINE void SetActiveOverlapingPickup(APickUp* PickupToSet) { ActiveOverlapingPickup = PickupToSet; }

};
