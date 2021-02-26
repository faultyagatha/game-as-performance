// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapon.h"

// Sets default values
AMainCharacter::AMainCharacter()
{

	PrimaryActorTick.bCanEverTick = true;
    //pulls towards the player if there is collision
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->TargetArmLength = 600.f; //distance at which camera follows
    CameraBoom->bUsePawnControlRotation = true; //rotate arm based on controller
    
    //set capsule size for collisions
    GetCapsuleComponent()->SetCapsuleSize(35.f, 100.f);
    
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
    
    BaseTurnRate = 65.f;
    BaseLookupRate = 65.f;
    
    //don't rotate when controller rotates
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationPitch = false;
    
    //turn the character in the direction she's moving
    GetCharacterMovement()->bOrientRotationToMovement = true;
    //only orient in the direction of the yaw movement
    GetCharacterMovement()->RotationRate = FRotator(0.f, 840.f, 0.f);
    GetCharacterMovement()->JumpZVelocity = 650.f;
    GetCharacterMovement()->AirControl = 0.2f;
    
    MaxHealth = 100.f;
    Health = 65.f;
    MaxStamina = 150.f; //lower for testing
    Stamina = 120.f;
    Pickups = 0;
    
    RunningSpeed = 650.f;
    SprintingSpeed = 950.f;
    
    bShiftKeyDown = false;
    bLeftMouseButtonDown = false;
    
    //initialise enums
    MovementStatus = EMovementStatus::EMS_Normal;
    StaminaStatus = EStaminaStatus::ESS_Normal;
    
    StaminaDrainRate = 25.f;
    MinSprintStamina = 50.f;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    float DeltaStamina = StaminaDrainRate * DeltaTime;
    
    switch(StaminaStatus)
    {
        case EStaminaStatus::ESS_Normal:
            if(bShiftKeyDown)
            {
                if(Stamina-DeltaStamina <= MinSprintStamina)
                {
                    SetStaminaStatus(EStaminaStatus::ESS_BelowMinimum);
                    Stamina -= DeltaStamina;
                }
                else
                {
                    Stamina -= DeltaStamina;
                }
                SetMovementStatus(EMovementStatus::EMS_Sprinting);
            }
            else //shift key is up
            {
                if(Stamina+DeltaStamina >= MaxStamina)
                {
                    Stamina = MaxStamina;
                }
                else
                {
                    Stamina += DeltaStamina;
                }
                SetMovementStatus(EMovementStatus::EMS_Normal);
            }
            break;
        case EStaminaStatus::ESS_BelowMinimum:
            if(bShiftKeyDown)
            {
                if(Stamina-DeltaStamina <= 0.f)
                {
                    SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
                    Stamina = 0.f;
                    SetMovementStatus(EMovementStatus::EMS_Normal);
                }
                else
                {
                    Stamina -= DeltaStamina;
                    SetMovementStatus(EMovementStatus::EMS_Sprinting);
                }
            }
            else //shift key is up
            {
                if(Stamina+DeltaStamina >= MinSprintStamina)
                {
                    SetStaminaStatus(EStaminaStatus::ESS_Normal);
                    Stamina += DeltaStamina;
                }
                else
                {
                    Stamina += DeltaStamina;
                }
                SetMovementStatus(EMovementStatus::EMS_Normal);
            }
            break;
        case EStaminaStatus::ESS_Exhausted:
            if(bShiftKeyDown)
            {
                Stamina = 0.f;
            }
            else //shift key is up
            {
                SetStaminaStatus(EStaminaStatus::ESS_ExhaustedRecovering);
                Stamina += DeltaStamina;
            }
            SetMovementStatus(EMovementStatus::EMS_Normal);
            break;
        case EStaminaStatus::ESS_ExhaustedRecovering:
            if(Stamina+DeltaStamina >= MinSprintStamina)
            {
                SetStaminaStatus(EStaminaStatus::ESS_Normal);
                Stamina += DeltaStamina;
            }
            else
            {
                Stamina += DeltaStamina;
            }
            SetMovementStatus(EMovementStatus::EMS_Normal);
            break;
        default:
            SetMovementStatus(EMovementStatus::EMS_Normal);
    }
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    
    //jump is inherited from character
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::ShiftKeyDown);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::ShiftKeyUp);
    
    PlayerInputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &AMainCharacter::LeftMouseButtonDown);
    PlayerInputComponent->BindAction("LeftMouseButton", IE_Released, this, &AMainCharacter::LeftMouseButtonUp);
    
    PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
    
    //pawn has mouse functionality so we can use it
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);
    
    PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookupRate", this, &AMainCharacter::LookupRate);

}

//characters inherit controllers by default
void AMainCharacter::MoveForward(float Value)
{
    if(Controller != nullptr && Value != 0.f)
    {
        //find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
        
        //get the forward direction vector from rotation matrix
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AMainCharacter::MoveRight(float Value)
{
    if(Controller != nullptr && Value != 0.f)
    {
        //find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
        
        //get the right direction vector from rotation matrix
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void AMainCharacter::TurnAtRate(float Rate)
{
    //how much we need to rotate 65 degrees each frame
    //GetWorld()->GetDeltaSeconds() is how we get DeltaTime
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookupRate(float Rate)
{
    AddControllerPitchInput(Rate * BaseLookupRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::DecrementHealth(float Amount)
{
    if(Health-Amount >= 0.f)
    {
        Health -= Amount;
        Die();
    }
    else
    {
        Health -= Amount;
    }
}

void AMainCharacter::IncrementPickups(int32 Amount)
{
        Pickups += Amount;

}

void AMainCharacter::Die()
{
    
}

void AMainCharacter::SetMovementStatus(EMovementStatus Status)
{
    MovementStatus = Status;
    if(MovementStatus == EMovementStatus::EMS_Sprinting)
    {
        GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
    }
}

void AMainCharacter::ShiftKeyDown()
{
    bShiftKeyDown = true;
}

void AMainCharacter::ShiftKeyUp()
{
    bShiftKeyDown = false;
}

void AMainCharacter::LeftMouseButtonDown()
{
    bLeftMouseButtonDown = true;
    if(ActiveOverlapingPickup)
    {
        AWeapon* Weapon = Cast<AWeapon>(ActiveOverlapingPickup);
        if(Weapon)
        {
            Weapon->Equip(this); //if the cast to weapon suceedes equip with weapon
            SetActiveOverlapingPickup(nullptr);
        }
    }
}

void AMainCharacter::LeftMouseButtonUp()
{
    bLeftMouseButtonDown = false;
}

void AMainCharacter::ShowPickupLocations()
{
    for(int32 i=0; i<PickupLocations.Num(); i++)
    {
        //debugging sphere
        UKismetSystemLibrary::DrawDebugSphere(this, PickupLocations[i], 25.f, 8, FLinearColor::Blue, 10.f, 0.5f);
    }
}

void AMainCharacter::SetEquipedWeapon(AWeapon* WeaponToSet)
{   if(EquipedWeapon)
    {
        EquipedWeapon->Destroy();
    }
    EquipedWeapon = WeaponToSet;
}


