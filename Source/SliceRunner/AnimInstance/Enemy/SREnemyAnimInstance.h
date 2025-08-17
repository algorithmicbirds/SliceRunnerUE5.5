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

    protected:
        UPROPERTY(EditAnywhere, BlueprintReadOnly)
        FVector TargetLocation;

        UPROPERTY(EditAnywhere, BlueprintReadOnly)
        bool bIsTargetVisible;
    };
