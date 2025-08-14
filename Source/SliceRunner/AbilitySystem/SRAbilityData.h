// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SRAbilityBase.h"
#include "SRAbilityData.generated.h"

USTRUCT(BlueprintType)
struct FSRAbilityActivationContext
{
    GENERATED_BODY()

public:
    FHitResult HitResults;
    FVector ActorLocation;
};

USTRUCT(BlueprintType)
struct FSRCurrentActorInfo
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
    TWeakObjectPtr<AActor> OwnerActor;

    UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
    TWeakObjectPtr<UAnimInstance> AnimInstance;

    UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
    TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

};