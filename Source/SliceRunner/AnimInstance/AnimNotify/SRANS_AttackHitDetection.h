// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SRANS_AttackHitDetection.generated.h"

class USRAbilityManagerComponent;
class USRMontageManager; 
    /**
 *
 */
UCLASS()
class SLICERUNNER_API USRANS_AttackHitDetection : public UAnimNotifyState
{
    GENERATED_BODY()

protected:
    virtual void NotifyBegin(
        USkeletalMeshComponent *MeshComp,
        UAnimSequenceBase *Animation,
        float TotalDuration,
        const FAnimNotifyEventReference &EventReference
    ) override;
    virtual void NotifyTick(
        USkeletalMeshComponent *MeshComp,
        UAnimSequenceBase *Animation,
        float FrameDeltaTime,
        const FAnimNotifyEventReference &EventReference
    ) override;

    UPROPERTY()
    TWeakObjectPtr<USRAbilityManagerComponent> AbilityManager;
 
    USRMontageManager* MontageManger = nullptr;
};
