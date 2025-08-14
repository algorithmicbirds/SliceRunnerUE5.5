// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/SRBaseAnimInstance.h"
#include "SRCharacterAnimInstance.generated.h"

class ASRBaseCharacter;
class UCharacterMovementComponent;
    /**
 *
 */
UCLASS()
class SLICERUNNER_API USRCharacterAnimInstance : public USRBaseAnimInstance
{
    GENERATED_BODY()
  public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

  protected:
    UPROPERTY()
    ASRBaseCharacter *Character;
    UPROPERTY()
    UCharacterMovementComponent *CharacterMovementComponent;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Locomotion")
    float GroundSpeed;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Locomotion")
    bool bHasAcceleration;
};
