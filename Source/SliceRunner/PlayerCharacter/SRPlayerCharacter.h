// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "Interfaces/Gate/GateRuleInterface.h"
#include "Interfaces/SRReceiveHitInterface.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "SRPlayerCharacter.generated.h"

class UCameraComponent;
class USRDataAsset_InputConfig;
class UStaticMeshComponent;
class USRGrappleDetectionComponent;
class USRAbilitySet;
class USRWallRunComponent;
class UAIPerceptionStimuliSourceComponent;


UCLASS()
class SLICERUNNER_API ASRPlayerCharacter : public ASRBaseCharacter, public IGateRuleInterface, public ISRReceiveHitInterface
{
    GENERATED_BODY()

public:
    ASRPlayerCharacter();
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
    virtual void SetAbilityFlags(const FGateAbilityFlags &InFlags) override;
    virtual void RecieveHitEvent() override;

protected:
    virtual void BeginPlay() override;
    virtual void Landed(const FHitResult &Hit) override;
    virtual void PossessedBy(AController *NewController) override;
    virtual void NotifyHit(
        UPrimitiveComponent *MyComp,
        AActor *Other,
        UPrimitiveComponent *OtherComp,
        bool bSelfMoved,
        FVector HitLocation,
        FVector HitNormal,
        FVector NormalImpulse,
        const FHitResult &Hit
    ) override;

private:
#pragma region Components

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USkeletalMeshComponent> FirstPersonMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UCameraComponent *FirstPersonCameraComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USRGrappleDetectionComponent> GrappleDetectionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USRWallRunComponent> WallRunComponent;

    UPROPERTY(EditDefaultsOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USRAbilitySet> AbilitySet;

    UPROPERTY(EditDefaultsOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAIPerceptionStimuliSourceComponent> StimuliSource;


#pragma endregion

#pragma region Inputs
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
    USRDataAsset_InputConfig *InputDataAssetConfig;

    void Input_Move(const FInputActionValue &InputActionValue);
    void Input_Look(const FInputActionValue &InputActionValue);
    void Input_Jump(const FInputActionValue &InputActionValue);
    void Input_Dash(const FInputActionValue &InputActionValue);
    void Input_Grapple(const FInputActionValue &InputActionValue);
    void Input_Attack(const FInputActionValue &InputActionValue);

#pragma endregion

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float DashStrafeOffsetScale = 3.0f;
};
