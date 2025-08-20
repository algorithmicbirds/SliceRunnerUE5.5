// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SRAIController.generated.h"

class UAISenseConfig_Sight;
struct FAIStimulus;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetInSightDelegate, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTargetOutofSightDelegate);

/**
 *
 */
UCLASS()
class SLICERUNNER_API ASRAIController : public AAIController
{
    GENERATED_BODY()
public:
    ASRAIController();
    FTargetInSightDelegate TargetDetected;
    FTargetOutofSightDelegate TargetLost;

protected:
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor &Other) const override;

    UFUNCTION()
    void OnEnemyPerceptionUpdated(AActor *Actor, FAIStimulus Stimulus);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UAIPerceptionComponent> EnemyAIPerception;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UAISenseConfig_Sight> EnemyAISightConfig;
};