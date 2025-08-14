// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstance/AnimNotify/SRAnimNotify_AttackWindow.h"
#include "GameplayTags/SRGameplayTags.h"
#include "AbilitySystem/SRMontageManager.h"
#include "AbilitySystem/SRAbilityManagerComponent.h"
#include "Debug/DebugHelper.h"

void USRAnimNotify_AttackWindow::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    if (!MeshComp)
    {
        return;
    }

    AActor *Owner = MeshComp->GetOwner();
    if (Owner)
    {
        if (USRAbilityManagerComponent *AMC = Owner->FindComponentByClass<USRAbilityManagerComponent>())
        {
            USRMontageManager *MM = AMC->GetMontagerManger();
            if (MM)
            {
                MM->BroadCastTagEvent(SRGameplayTags::EventTag_AttackWindow);
            }
        }
    }
}
