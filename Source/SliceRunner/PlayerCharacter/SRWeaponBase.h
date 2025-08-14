// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "SRWeaponBase.generated.h"

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SLICERUNNER_API USRWeaponBase : public USkeletalMeshComponent
{
    GENERATED_BODY()
};
