// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter/SRPlayerCharacter.h"
#include "Input/SRDataAsset_InputConfig.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameplayTags/SRGameplayTags.h"
#include "Input/SREnhancedInputComponent.h"
#include "Debug/DebugHelper.h"
#include "PlayerCharacter/SRGrappleDetectionComponent.h"
#include "PlayerCharacter/SRWallRunComponent.h"
#include "PlayerCharacter/SRWeaponBase.h"
#include "AbilitySystem/SRAbilitySet.h"
#include "AbilitySystem/SRAbilityManagerComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

ASRPlayerCharacter::ASRPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    GetCapsuleComponent()->InitCapsuleSize(32.0f, 96.0f);

    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    GetMesh()->SetupAttachment(FirstPersonCameraComponent);

    WeaponMesh->SetupAttachment(GetMesh(), TEXT("katana_socket"));

    GrappleDetectionComponent = CreateDefaultSubobject<USRGrappleDetectionComponent>(TEXT("GrappleDetectionComponent"));
    WallRunComponent = CreateDefaultSubobject<USRWallRunComponent>(TEXT("WallRunComponent"));

    StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSource"));
    StimuliSource->RegisterForSense(UAISense_Sight::StaticClass());
    StimuliSource->RegisterWithPerceptionSystem();
}

void ASRPlayerCharacter::BeginPlay() { Super::BeginPlay(); }

void ASRPlayerCharacter::Landed(const FHitResult &Hit)
{
    Super::Landed(Hit);
    WallRunComponent->StopWallRun();
    SRAMC->StopAbilityByTag(SRGameplayTags::AbilityTag_Dash);
}

void ASRPlayerCharacter::PossessedBy(AController *NewController)
{
    Super::PossessedBy(NewController);
    checkf(AbilitySet, TEXT("Forgot to assign Ability Set To player Character"));
    if (SRAMC)
    {
        AbilitySet->GiveAbilityToManager(SRAMC);
    }
}

void ASRPlayerCharacter::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ASRPlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    checkf(InputDataAssetConfig, TEXT("Forgot to assign a valid DataAsset_InputConfig in the editor!"));

    ULocalPlayer *LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
    UEnhancedInputLocalPlayerSubsystem *Subsystem =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
    check(Subsystem);
    Subsystem->AddMappingContext(InputDataAssetConfig->DefaultMappingContext, 0);

    USREnhancedInputComponent *SRInputComp = CastChecked<USREnhancedInputComponent>(PlayerInputComponent);

    SRInputComp->BindNativeInputAction(
        InputDataAssetConfig,
        SRGameplayTags::InputTag_Move,
        ETriggerEvent::Triggered,
        this,
        &ASRPlayerCharacter::Input_Move
    );

    SRInputComp->BindNativeInputAction(
        InputDataAssetConfig,
        SRGameplayTags::InputTag_Look,
        ETriggerEvent::Triggered,
        this,
        &ASRPlayerCharacter::Input_Look
    );

    SRInputComp->BindNativeInputAction(
        InputDataAssetConfig,
        SRGameplayTags::InputTag_Jump,
        ETriggerEvent::Triggered,
        this,
        &ASRPlayerCharacter::Input_Jump
    );

    SRInputComp->BindNativeInputAction(
        InputDataAssetConfig,
        SRGameplayTags::InputTag_Dash,
        ETriggerEvent::Triggered,
        this,
        &ASRPlayerCharacter::Input_Dash
    );

    SRInputComp->BindNativeInputAction(
        InputDataAssetConfig,
        SRGameplayTags::InputTag_Grapple,
        ETriggerEvent::Triggered,
        this,
        &ASRPlayerCharacter::Input_Grapple
    );

    SRInputComp->BindNativeInputAction(
        InputDataAssetConfig,
        SRGameplayTags::InputTag_Attack,
        ETriggerEvent::Triggered,
        this,
        &ASRPlayerCharacter::Input_Attack
    );

    SRInputComp->BindNativeInputAction(
        InputDataAssetConfig,
        SRGameplayTags::InputTag_Attack,
        ETriggerEvent::Triggered,
        this,
        &ASRPlayerCharacter::Input_Respawn
    );
}

void ASRPlayerCharacter::SetAbilityFlags(const FGateAbilityFlags &InFlags)
{
    if (InFlags.bCanGrapple)
    {
        GrappleDetectionComponent->EnableGrappleDetection();
    }
    else
    {
        GrappleDetectionComponent->DisableGrappleDetection();
    }
}

void ASRPlayerCharacter::RecieveHitEvent()
{
    Debug::Print("Receieve Hit player");
    SRAMC->StartAbilityByTag(SRGameplayTags::AbilityTag_Death);
}

#pragma region Inputs
void ASRPlayerCharacter::Input_Move(const FInputActionValue &InputActionValue)
{
    const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
    const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

    if (MovementVector.Y != 0.0f)
    {
        const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
        AddMovementInput(ForwardDirection, MovementVector.Y);
    }

    if (MovementVector.X != 0.0f)
    {
        if (WallRunComponent->IsWallRunning())
        {
            WallRunComponent->StopWallRun();
        }
        const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
        if (SRAMC->HasAbilityActiveTag(SRGameplayTags::AbilityTag_Dash))
        {
            float DeltaTime = GetWorld()->GetDeltaSeconds();
            AddActorWorldOffset(RightDirection * MovementVector.X * DashStrafeOffsetScale * DeltaTime);
        }
        else
        {
            AddMovementInput(RightDirection, MovementVector.X);
        }
    }
}

void ASRPlayerCharacter::Input_Look(const FInputActionValue &InputActionValue)
{
    const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
    if (LookAxisVector.X != 0.0f)
    {
        AddControllerYawInput(LookAxisVector.X);
    }

    if (LookAxisVector.Y != 0.0f)
    {
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void ASRPlayerCharacter::Input_Jump(const FInputActionValue &InputActionValue)
{
    if (InputActionValue.Get<bool>())
    {
        SRAMC->StartAbilityByTag(SRGameplayTags::AbilityTag_Jump);
    }
    else
    {
        SRAMC->StopAbilityByTag(SRGameplayTags::AbilityTag_Jump);
    }
}

void ASRPlayerCharacter::Input_Dash(const FInputActionValue &InputActionValue)
{
    if (InputActionValue.Get<bool>())
    {
        SRAMC->StartAbilityByTag(SRGameplayTags::AbilityTag_Dash);
    }
    else
    {
        SRAMC->StopAbilityByTag(SRGameplayTags::AbilityTag_Dash);
    }
}

void ASRPlayerCharacter::Input_Grapple(const FInputActionValue &InputActionValue)
{
    if (InputActionValue.Get<bool>())
    {
        FSRAbilityActivationContext Context;
        Context.HitResults = GrappleDetectionComponent->GetGrappleHitResult();
        SRAMC->StartAbilityByTag(SRGameplayTags::AbilityTag_Grapple, Context);
    }
    else
    {
        SRAMC->StopAbilityByTag(SRGameplayTags::AbilityTag_Grapple);
    }
}

void ASRPlayerCharacter::Input_Attack(const FInputActionValue &InputActionValue)
{
    if (InputActionValue.Get<bool>())
    {
        SRAMC->StartAbilityByTag(SRGameplayTags::AbilityTag_Attack);
    }
    else
    {
        SRAMC->StopAbilityByTag(SRGameplayTags::AbilityTag_Attack);
    }
}

void ASRPlayerCharacter::Input_Respawn(const FInputActionValue &InputActionValue)
{
    if (InputActionValue.Get<bool>())
    {
        GetCharacterMovement()->SetMovementMode(MOVE_Walking);
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }
}

#pragma endregion

void ASRPlayerCharacter::NotifyHit(
    UPrimitiveComponent *MyComp,
    AActor *Other,
    UPrimitiveComponent *OtherComp,
    bool bSelfMoved,
    FVector HitLocation,
    FVector HitNormal,
    FVector NormalImpulse,
    const FHitResult &Hit
)
{
    if (WallRunComponent->CheckForWall(Hit))
    {
        WallRunComponent->StartWallRun(Hit);
    }
}
