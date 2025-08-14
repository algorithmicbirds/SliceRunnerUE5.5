// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "SRAbilitySet.generated.h"

class USRAbilityBase;
class USRAbilityManagerComponent;

USTRUCT(BlueprintType)
struct FSRGameplayAbility
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<USRAbilityBase> Ability = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "AbilityTag"))
    FGameplayTag AbilityTag;
};
/**
 *
 */
UCLASS()
class SLICERUNNER_API USRAbilitySet : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    void GiveAbilityToManager(USRAbilityManagerComponent *AMC);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta = (TitleProperty = Ability))
    TArray<FSRGameplayAbility> GrantedGameplayAbilities;
};
