// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Input/SRDataAsset_InputConfig.h"
#include "SREnhancedInputComponent.generated.h"

/**
 *
 */
UCLASS()
class SLICERUNNER_API USREnhancedInputComponent : public UEnhancedInputComponent
{
    GENERATED_BODY()

  public:
    template <class UserObject, typename CallBackFunc>
    void BindNativeInputAction(
        const USRDataAsset_InputConfig *InInputConfig,
        const FGameplayTag &InInputTag,
        ETriggerEvent TriggerEvent,
        UserObject *ContextObject,
        CallBackFunc Func
    );
};

template <class UserObject, typename CallBackFunc>
inline void USREnhancedInputComponent::BindNativeInputAction(
    const USRDataAsset_InputConfig *InInputConfig,
    const FGameplayTag &InInputTag,
    ETriggerEvent TriggerEvent,
    UserObject *ContextObject,
    CallBackFunc Func
)
{
    checkf(InInputConfig, TEXT("Input Config Datasset is null, cannot proceed with binding"));
    if (UInputAction *FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
    {
        BindAction(FoundAction, TriggerEvent, ContextObject, Func);
    }
}
