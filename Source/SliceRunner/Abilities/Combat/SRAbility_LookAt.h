// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SRAbilityBase.h"
#include "SRAbility_LookAt.generated.h"

/**
 * 
 */
UCLASS()
class SLICERUNNER_API USRAbility_LookAt : public USRAbilityBase
{
	GENERATED_BODY()
    virtual void ActivateAbility(const FSRAbilityActivationContext &Context) override;
    virtual void EndAbility() override;
};
