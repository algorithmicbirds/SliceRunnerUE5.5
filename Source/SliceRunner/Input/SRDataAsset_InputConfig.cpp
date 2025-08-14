// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/SRDataAsset_InputConfig.h"

UInputAction *USRDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag &InInputTag) const
{
    for (const FSRInputActionConfig &InputActionConfig : NativeInputActions)
    {
        if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
        {
            return InputActionConfig.InputAction;
        }
    }
    return nullptr;
}
