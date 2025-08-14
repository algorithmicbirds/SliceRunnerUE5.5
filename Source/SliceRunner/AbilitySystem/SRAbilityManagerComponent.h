// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitySystem/SRAbilityData.h"
#include "GameplayTagContainer.h"
#include "SRAbilityManagerComponent.generated.h"

class USRAbilityBase;
class USRMontageManager;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SLICERUNNER_API USRAbilityManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USRAbilityManagerComponent(const FObjectInitializer& ObjectInitializer);
    void InitActorInfo(AActor *OwnerActor);
    void GiveAbility(FGameplayTag AbilityTag, USRAbilityBase *AbilityClass);
    void StartAbilityByTag(
        FGameplayTag AbilityTag, const FSRAbilityActivationContext &Context = FSRAbilityActivationContext{}
    );
    void StopAbilityByTag(FGameplayTag AbilityTag);
    bool HasAbilityActiveTag(FGameplayTag AbilityTag);
    USRMontageManager *GetMontagerManger() const;

protected:
    virtual void BeginPlay() override;
    UPROPERTY()
    TMap<FGameplayTag, TObjectPtr<USRAbilityBase>> AbilityMap;
    FGameplayTagContainer ActiveAbilities;
    FSRCurrentActorInfo CachedActorInfo;

    UPROPERTY()
    TObjectPtr<USRMontageManager> MontageManger;

};
