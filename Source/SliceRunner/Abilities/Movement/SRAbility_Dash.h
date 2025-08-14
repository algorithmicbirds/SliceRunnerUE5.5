// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SRAbilityBase.h"
#include "SRAbility_Dash.generated.h"

UCLASS()
class SLICERUNNER_API USRAbility_Dash : public USRAbilityBase
{
    GENERATED_BODY()
public:
    USRAbility_Dash();

protected:
    virtual void ActivateAbility(const FSRAbilityActivationContext &Context) override;
    virtual void EndAbility() override;
};
