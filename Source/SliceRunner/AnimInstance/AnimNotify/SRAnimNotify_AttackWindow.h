// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SRAnimNotify_AttackWindow.generated.h"

class USRMontageManager;
/**
 * 
 */
UCLASS()
class SLICERUNNER_API USRAnimNotify_AttackWindow : public UAnimNotify
{
	GENERATED_BODY()
    virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;

    protected:
    TWeakObjectPtr<USRMontageManager> MontageManager;
};
