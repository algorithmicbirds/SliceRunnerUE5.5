// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SRMontageManager.generated.h"

class USRAbilityBase;
class USRBaseAnimInstance;

DECLARE_MULTICAST_DELEGATE(FMontageWaitDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FMontageTaggedEvent, const FGameplayTag &);



USTRUCT(BlueprintType)
struct FSRCurrentMontageInfo
{
    GENERATED_BODY()

public:
    UPROPERTY()
    TWeakObjectPtr<UAnimMontage> CurrentPlayingMontage = nullptr;

    UPROPERTY()
    TWeakObjectPtr<USRAbilityBase> CurrentPlayingAbility = nullptr;

    FSRCurrentMontageInfo() = default;
};

/**
 *
 */
UCLASS()
class SLICERUNNER_API USRMontageManager : public UObject
{
    GENERATED_BODY()

public:
    FMontageWaitDelegate OnMontageCompleted;
    FMontageWaitDelegate OnMontageInterrupted;
    

    bool TryAndPlayMontage(
        USRAbilityBase *Ability,
        UAnimMontage *MontageToPlay,
        USRBaseAnimInstance *AnimInstance,
        bool bIsAllowedToInterruptOther,
        float PlayRate = 1.0f
    );

    void BroadCastTagEvent(FGameplayTag EventTag);

    template <typename UserClass>
    void
    RegisterMontageCompleteCallback(UserClass *Listener, typename TMemFunPtrType<false, UserClass, void()>::Type FUNC);
    template <typename UserClass>
    void
    RegisterMontageInterruptedCallback(UserClass *Listener, typename TMemFunPtrType<false, UserClass, void()>::Type FUNC);
    template <typename UserClass>
    void RegisterEventMontageCallback(
        UserClass *Listener,
        typename TMemFunPtrType<false, UserClass, void(const FGameplayTag &)>::Type Func,
        FGameplayTag EventTag
    );


protected:
    void ClearAnimatingAbility();
    void StopCurrentMontage(float OverrideBlendOutTime = -1.0f);
    float PlayMontage(
        USRAbilityBase *AnimatingAbility, UAnimMontage *Montage, float InPlayRate, float StartTimeSeconds = 0.0f
    );
    void StopPlayingMontage();
    UFUNCTION()
    void OnMontageEnded(UAnimMontage *Montage, bool bInterrupted);
    // UFUNCTION()
    // void OnMontageInterrupted(UAnimMontage *Montage);

    UFUNCTION()
    void OnMontageBlendOut(UAnimMontage *Montage, bool bInterrupted);

    FOnMontageEnded OnMontageEndedDelegate;
    FOnMontageBlendingOutStarted OnMontageBlendOutStartedDelegate;
    
    FSRCurrentMontageInfo CurrentMontageInfo;

    UPROPERTY()
    TWeakObjectPtr<USRBaseAnimInstance> AnimInstance;

    FAnimMontageInstance *ActiveMontageInstance = nullptr; 
    bool bIsAllowedToInterrupt = false;
    TMap<FGameplayTag, FMontageTaggedEvent> TagDelegates;
};

template <typename UserClass>
inline void USRMontageManager::RegisterMontageCompleteCallback(
    UserClass *Listener, typename TMemFunPtrType<false, UserClass, void()>::Type FUNC
)
{
    OnMontageCompleted.RemoveAll(Listener);
    OnMontageCompleted.AddUObject(Listener, FUNC);
}

template <typename UserClass>
inline void USRMontageManager::RegisterMontageInterruptedCallback(
    UserClass *Listener, typename TMemFunPtrType<false, UserClass, void()>::Type FUNC
)
{
    OnMontageInterrupted.RemoveAll(Listener);
    OnMontageInterrupted.AddUObject(Listener, FUNC);
}

template <typename UserClass>
inline void USRMontageManager::RegisterEventMontageCallback(
    UserClass *Listener,
    typename TMemFunPtrType<false, UserClass, void(const FGameplayTag &)>::Type Func,
    FGameplayTag EventTag
)
{
    FMontageTaggedEvent &Delegate = TagDelegates.FindOrAdd(EventTag);
    Delegate.RemoveAll(Listener);
    Delegate.AddUObject(Listener, Func);
}
