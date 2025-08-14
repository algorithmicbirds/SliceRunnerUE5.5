// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/SRAbilityManagerComponent.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "AbilitySystem/SRAbilityBase.h"
#include "Debug/DebugHelper.h"
#include "AbilitySystem/SRMontageManager.h"

USRAbilityManagerComponent::USRAbilityManagerComponent(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.bCanEverTick = false;
    MontageManger = CreateDefaultSubobject<USRMontageManager>(TEXT("MontageManager"));
}

void USRAbilityManagerComponent::InitActorInfo(AActor *OwnerActor)
{
    if (OwnerActor == nullptr)
    {
        Debug::Print("Owner Actor Is not valid");
        return;
    }
    CachedActorInfo.OwnerActor = OwnerActor;
    if (ASRBaseCharacter *Character = Cast<ASRBaseCharacter>(OwnerActor))
    {
        if (UAnimInstance *AnimInstance = Character->GetMesh()->GetAnimInstance())
        {
            CachedActorInfo.AnimInstance = AnimInstance;
        }
    }
}

void USRAbilityManagerComponent::GiveAbility(FGameplayTag AbilityTag, USRAbilityBase *AbilityInstance)
{
    if (AbilityInstance)
    {
        AbilityInstance->SetActorInfo(&CachedActorInfo);
        AbilityInstance->MontageManger = MontageManger;
        AbilityInstance->SetAbilityTag(AbilityTag);
        AbilityInstance->AbilityManager = this;
        AbilityMap.Add(AbilityTag, AbilityInstance);
    }
}

void USRAbilityManagerComponent::StartAbilityByTag(FGameplayTag AbilityTag, const FSRAbilityActivationContext &Context)
{
    if (AbilityMap.Contains(AbilityTag))
    {
        USRAbilityBase *Ability = AbilityMap[AbilityTag];
        ActiveAbilities.AddTag(AbilityTag);
        Ability->ActivateAbility(Context);
    }
}

void USRAbilityManagerComponent::StopAbilityByTag(FGameplayTag AbilityTag)
{
    if (!ActiveAbilities.HasTagExact(AbilityTag))
    {
        return;
    }

    if (AbilityMap.Contains(AbilityTag))
    {
        USRAbilityBase *Ability = AbilityMap[AbilityTag];
        Ability->EndAbility();
        ActiveAbilities.RemoveTag(AbilityTag);
    }
}

bool USRAbilityManagerComponent::HasAbilityActiveTag(FGameplayTag AbilityTag)
{
    return ActiveAbilities.HasTagExact(AbilityTag);
}

USRMontageManager *USRAbilityManagerComponent::GetMontagerManger() const { return MontageManger; }

void USRAbilityManagerComponent::BeginPlay() { Super::BeginPlay(); }
