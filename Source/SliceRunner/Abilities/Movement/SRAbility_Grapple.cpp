// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Movement/SRAbility_Grapple.h"
#include "PlayerCharacter/SRPlayerCharacter.h"
#include "AbilitySystem/SRAbilityData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Debug/DebugHelper.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

USRAbility_Grapple::USRAbility_Grapple() {}
void USRAbility_Grapple::ActivateAbility(const FSRAbilityActivationContext &Context)
{
    Character = GetSRCharacter();
    FHitResult GrappleHit = Context.HitResults;
    Grapple(GrappleHit);
}

void USRAbility_Grapple::EndAbility() { ResetGrappleState(); }

void USRAbility_Grapple::Grapple(const FHitResult &HitResult)
{
    if (!HitResult.bBlockingHit)
    {
        return;
    }

    CurrentGrappleTarget = HitResult.GetActor()->GetActorLocation();

    Character->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
    Character->GetCharacterMovement()->StopMovementImmediately();
    Character->GetCharacterMovement()->GravityScale = 0.0f;

    SpawnBeamEffect(CurrentGrappleTarget);
    GetWorld()->GetTimerManager().SetTimer(
        UpdateGrappleMovementTimerHandle, this, &USRAbility_Grapple::UpdateGrappleMovement, 0.06f, true
    );
}

void USRAbility_Grapple::UpdateGrappleMovement()
{
    if (!Character)
        return;

    FVector ToTarget = CurrentGrappleTarget - Character->GetActorLocation();
    float Distance = ToTarget.Size();

    if (Distance < 300.f)
    {
        ResetGrappleState();
    }
    else
    {
        FVector Direction = ToTarget.GetSafeNormal();
        Character->GetCharacterMovement()->Velocity = Direction * GrappleSpeed;

        if (ActiveBeamFX)
        {
            ActiveBeamFX->SetVectorParameter("EndPoint", CurrentGrappleTarget);
        }
    }
}

void USRAbility_Grapple::ResetGrappleState()
{
    if (!Character)
        return;

    Character->GetCharacterMovement()->GravityScale = 1.0f;
    Character->GetCharacterMovement()->SetMovementMode(MOVE_Falling);

    GetWorld()->GetTimerManager().ClearTimer(UpdateGrappleMovementTimerHandle);
    DestroyBeamEffect();
}

void USRAbility_Grapple::SpawnBeamEffect(const FVector &Target)
{
    if (!GrappleBeamFX || !Character)
        return;

    FVector Start = Character->GetMesh()->GetSocketLocation(GrappleStartSocketName);
    ActiveBeamFX = UNiagaraFunctionLibrary::SpawnSystemAttached(
        GrappleBeamFX,
        Character->GetMesh(),
        GrappleStartSocketName,
        FVector::ZeroVector,
        FRotator::ZeroRotator,
        EAttachLocation::SnapToTarget,
        true
    );

    if (ActiveBeamFX)
    {
        ActiveBeamFX->SetVectorParameter("EndPoint", Target);
    }
}

void USRAbility_Grapple::DestroyBeamEffect()
{
    if (ActiveBeamFX)
    {
        ActiveBeamFX->Deactivate();
        ActiveBeamFX = nullptr;
    }
}
