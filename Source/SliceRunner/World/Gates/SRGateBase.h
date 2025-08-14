// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Gate/GateRuleInterface.h"
#include "SRGateBase.generated.h"

class UBoxComponent;

UCLASS()
class SLICERUNNER_API ASRGateBase : public AActor
{
    GENERATED_BODY()

public:
    ASRGateBase();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gate Ability")
    FGateAbilityFlags AbilityFlags;

protected:
    virtual void BeginPlay() override;
    const FGateAbilityFlags &GetGateAbilities() const;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent *GateTrigger;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent *OverlappedComp,
        AActor *OtherActor,
        UPrimitiveComponent *OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult &SweepResult
    );
};
