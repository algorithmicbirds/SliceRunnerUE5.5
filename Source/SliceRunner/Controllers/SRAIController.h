// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SRAIController.generated.h"

class UAISenseConfig_Sight;
struct FAIStimulus;
/**
 *
 */
UCLASS()
class SLICERUNNER_API ASRAIController : public AAIController
{
    GENERATED_BODY()
public:
    ASRAIController();

protected:
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor &Other) const override;

    UFUNCTION()
    void OnEnemyPerceptionUpdated(AActor *Actor, FAIStimulus Stimulus);
    virtual void OnPossess(APawn *InPawn) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UAIPerceptionComponent> EnemyAIPerception;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UAISenseConfig_Sight> EnemyAISightConfig;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UBehaviorTree> BehaviorTree;

    UPROPERTY(EditDefaultsOnly)
    FName TargetActorBlackBoardValue;
};