// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Combat/SRAbility_Attack.h"
#include "Debug/DebugHelper.h"
#include "AnimInstance/SRBaseAnimInstance.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "GameplayTags/SRGameplayTags.h"
#include "AbilitySystem/SRMontageManager.h"
#include "PlayerCharacter/SRWeaponBase.h"
#include "Interfaces/SRReceiveHitInterface.h"

void USRAbility_Attack::ActivateAbility(const FSRAbilityActivationContext &Context)
{
    Super::ActivateAbility(Context);
    Character = GetSRCharacter();
    AnimInstance = GetSRAnimInstance();
    WeaponMesh = Character ? Character->WeaponMesh : nullptr;

    if (!Character || !AnimInstance || !WeaponMesh)
    {
        RequestEndAbility();
        return;
    }

    PlayAttackMontage();
}

void USRAbility_Attack::PlayAttackMontage()
{
    if (!AttackAnimComboMantages.IsValidIndex(AttackCount))
    {
        RequestEndAbility();
        return;
    }

    bool bMontagePlayed = MontageManger->TryAndPlayMontage(
        this, AttackAnimComboMantages[AttackCount], AnimInstance, bIsAllowedToInterrupt
    );

    if (!bMontagePlayed)
    {
        RequestEndAbility();
        return;
    }

    MontageManger->RegisterMontageCompleteCallback(this, &USRAbility_Attack::OnMontageCompleted);
    MontageManger->RegisterMontageInterruptedCallback(this, &USRAbility_Attack::OnMontageInterrupted);
    MontageManger->RegisterEventMontageCallback(
        this, &USRAbility_Attack::AttackWindowOpened, SRGameplayTags::EventTag_AttackWindow
    );
    MontageManger->RegisterEventMontageCallback(
        this, &USRAbility_Attack::AttackState, SRGameplayTags::EventTag_AttackState
    );
}

void USRAbility_Attack::EndAbility() {}

void USRAbility_Attack::UpdateAttackIndex() { AttackCount = (AttackCount + 1) % AttackAnimComboMantages.Num(); }

void USRAbility_Attack::OnMontageCompleted() { UpdateAttackIndex(); }

void USRAbility_Attack::OnMontageInterrupted() { UpdateAttackIndex(); }

void USRAbility_Attack::AttackWindowOpened(const FGameplayTag &Tag) { UpdateAttackIndex(); }

void USRAbility_Attack::AttackState(const FGameplayTag &Tag)
{
    if (!Character || !WeaponMesh)
    {
        return;
    }
    FHitResult HitInfo;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetSRCharacter());
    FVector BladeBase = WeaponMesh->GetSocketLocation(HitDetectionStartSocket);
    FVector BladeTip = WeaponMesh->GetSocketLocation(HitDetectionEndSocket);

    bool bRayHit = GetWorld()->LineTraceSingleByChannel(
        HitInfo, BladeBase, BladeTip, ECC_Pawn, Params, FCollisionResponseParams()
    );
    // Debug::DrawLineDebug(GetWorld(), BladeBase, BladeTip, HitInfo, 3.0f);
    if (bRayHit)
    {
        if (AActor *HitActor = HitInfo.GetActor())
        {
            if (ISRReceiveHitInterface *HitReceiveInterface = Cast<ISRReceiveHitInterface>(HitActor))
            {
                HitReceiveInterface->RecieveHitEvent();
            }
        }
    }
}