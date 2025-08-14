// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstance/AnimNotify/SRANS_AttackHitDetection.h"
#include "Debug/DebugHelper.h"
#include "AbilitySystem/SRAbilityManagerComponent.h"
#include "AbilitySystem/SRMontageManager.h"
#include "GameplayTags/SRGameplayTags.h"

void USRANS_AttackHitDetection::NotifyBegin(
    USkeletalMeshComponent *MeshComp,
    UAnimSequenceBase *Animation,
    float TotalDuration,
    const FAnimNotifyEventReference &EventReference
)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
    AActor *Owner = MeshComp->GetOwner();
    if (Owner)
    {
        AbilityManager = Owner->FindComponentByClass<USRAbilityManagerComponent>();
        if (AbilityManager.IsValid())
        {
            MontageManger = AbilityManager.Get()->GetMontagerManger();
        }
    }
}

void USRANS_AttackHitDetection::NotifyTick(
    USkeletalMeshComponent *MeshComp,
    UAnimSequenceBase *Animation,
    float FrameDeltaTime,
    const FAnimNotifyEventReference &EventReference
)
{
    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
    if (MontageManger)
    {
        MontageManger->BroadCastTagEvent(SRGameplayTags::EventTag_AttackState);
    }
}
