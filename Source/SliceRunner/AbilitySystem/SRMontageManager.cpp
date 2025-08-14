// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/SRMontageManager.h"
#include "AbilitySystem/SRAbilityBase.h"
#include "AnimInstance/SRBaseAnimInstance.h"
#include "Debug/DebugHelper.h"

bool USRMontageManager::TryAndPlayMontage(
    USRAbilityBase *Ability,
    UAnimMontage *MontageToPlay,
    USRBaseAnimInstance *AbilityAnimInstance,
    bool bIsAllowedToInterruptOthers,
    float PlayRate
)
{
    if (!Ability || !MontageToPlay || !AbilityAnimInstance)
    {
        Debug::Print("Invalid parameters passed to TryAndPlayMontage");
        return false;
    }
    bIsAllowedToInterrupt = bIsAllowedToInterruptOthers;
    AnimInstance = AbilityAnimInstance;
    FString DebugMsg = FString::Printf(TEXT("Montage Name %s"), *GetNameSafe(MontageToPlay));
    // Debug::Print(DebugMsg);
    bool bCanPlay = bIsAllowedToInterrupt || (Ability->GetCurrentAnimMontage() != MontageToPlay);
    if (bCanPlay)
    {
        if (PlayMontage(Ability, MontageToPlay, PlayRate) > 0)
        {
            OnMontageEndedDelegate.BindUObject(this, &USRMontageManager::OnMontageEnded);
            AnimInstance->Montage_SetEndDelegate(OnMontageEndedDelegate, MontageToPlay);

            OnMontageBlendOutStartedDelegate.BindUObject(this, &USRMontageManager::OnMontageBlendOut);
            AnimInstance->Montage_SetBlendingOutDelegate(OnMontageBlendOutStartedDelegate, MontageToPlay);
            return true;
        }
    }
    return false;
}

void USRMontageManager::BroadCastTagEvent(FGameplayTag EventTag)
{
    for (const TPair<FGameplayTag, FMontageTaggedEvent> &Pair : TagDelegates)
    {
        if (EventTag.MatchesTag(Pair.Key))
        {
            Pair.Value.Broadcast(EventTag);
        }
    }
}

float USRMontageManager::PlayMontage(
    USRAbilityBase *AnimatingAbility, UAnimMontage *MontageToPlay, float InPlayRate, float StartTimeSeconds
)
{
    float Duration = -1.f;
    UAnimInstance *AnimInstanceToPlay = AnimInstance.Get();
    if (AnimInstanceToPlay && MontageToPlay)
    {
        Duration = AnimInstance->Montage_Play(
            MontageToPlay, InPlayRate, EMontagePlayReturnType::MontageLength, StartTimeSeconds
        );
        CurrentMontageInfo.CurrentPlayingAbility = AnimatingAbility;
        CurrentMontageInfo.CurrentPlayingMontage = MontageToPlay;
        ActiveMontageInstance = AnimInstance->GetActiveInstanceForMontage(MontageToPlay);
        if (AnimatingAbility)
        {
            AnimatingAbility->SetCurrentAnimMontage(MontageToPlay);
        }
    }

    return Duration;
}

void USRMontageManager::ClearAnimatingAbility()
{
    if (USRAbilityBase *Ability = CurrentMontageInfo.CurrentPlayingAbility.Get())
    {
        Ability->SetCurrentAnimMontage(nullptr);
    }
}

void USRMontageManager::OnMontageEnded(UAnimMontage *Montage, bool bInterrupted)
{
    if (!bInterrupted)
    {
        OnMontageCompleted.Broadcast();
        StopPlayingMontage();
        ClearAnimatingAbility();
    }
    else
    {
        // Debug::Print("Montage einterrupted");
    }
}


void USRMontageManager::OnMontageBlendOut(UAnimMontage *Montage, bool bInterrupted)
{
    if (bInterrupted)
    {
        if (bIsAllowedToInterrupt)
        {
            OnMontageInterrupted.Broadcast();
        }
        // Debug::Print("Montagte was interrupted So blend out delgate");
    }
}

void USRMontageManager::StopPlayingMontage()
{

    if (ActiveMontageInstance)
    {
        ActiveMontageInstance->OnMontageEnded.Unbind();
        ActiveMontageInstance->OnMontageBlendingOutStarted.Unbind();
    }
    else
    {
        Debug::Print("Active instance is null");
    }
}

void USRMontageManager::StopCurrentMontage(float OverrideBlendOutTime)
{
    UAnimMontage *MontageToStop = CurrentMontageInfo.CurrentPlayingMontage.Get();
    bool bShouldStopMontage = AnimInstance.Get() && MontageToStop && !AnimInstance->Montage_GetIsStopped(MontageToStop);

    if (bShouldStopMontage)
    {
        const float BlendOutTime =
            (OverrideBlendOutTime >= 0.0f ? OverrideBlendOutTime : MontageToStop->BlendOut.GetBlendTime());

        AnimInstance->Montage_Stop(BlendOutTime, MontageToStop);
    }
}
