// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/SRCharacterAnimInstance.h"
#include "SREnemyAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class SLICERUNNER_API USREnemyAnimInstance : public USRCharacterAnimInstance
{
    GENERATED_BODY()

public:
    void SetTargetLocation(FVector InLocation) { TargetLocation = InLocation; }
    void SetTargetVisible(bool InTargetVisible) { bIsTargetVisible = InTargetVisible; }
    void SetIsMovingAwayFromTarget(bool InIsMovingAwayFromEnemy) { bIsMovingAwayFromTarget = InIsMovingAwayFromEnemy; }
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
    

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FVector TargetLocation;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bIsTargetVisible = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Direction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bIsMovingAwayFromTarget = false;

};
