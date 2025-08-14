// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SRAbilityBase.h"
#include "SRAbility_Death.generated.h"

/**
 * 
 */
UCLASS()
class SLICERUNNER_API USRAbility_Death : public USRAbilityBase
{
	GENERATED_BODY()
protected:
        virtual void ActivateAbility(const FSRAbilityActivationContext &Context) override;
};
