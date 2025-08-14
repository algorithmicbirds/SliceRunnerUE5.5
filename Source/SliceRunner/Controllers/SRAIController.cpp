// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/SRAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Debug/DebugHelper.h"
#include "BehaviorTree/BlackboardComponent.h"


ASRAIController::ASRAIController()
{
    EnemyAISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("EnemyAISightConfig"));
    EnemyAISightConfig->DetectionByAffiliation.bDetectEnemies = true;
    EnemyAISightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    EnemyAISightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    EnemyAISightConfig->SightRadius = 10000.0f;
    EnemyAISightConfig->LoseSightRadius = 1000.0f;
    EnemyAISightConfig->PeripheralVisionAngleDegrees = 360.0f;

    EnemyAIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyAIPerception"));
    EnemyAIPerception->ConfigureSense(*EnemyAISightConfig);
    EnemyAIPerception->SetDominantSense(UAISenseConfig_Sight::StaticClass());
    EnemyAIPerception->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ASRAIController::OnEnemyPerceptionUpdated);
    SetGenericTeamId(FGenericTeamId(2));
}

ETeamAttitude::Type ASRAIController::GetTeamAttitudeTowards(const AActor &Other) const
{
    const APawn *OtherPawn = Cast<const APawn>(&Other);
    const IGenericTeamAgentInterface *OtherAgent = Cast<const IGenericTeamAgentInterface>(OtherPawn->GetController());
    if (OtherAgent && OtherAgent->GetGenericTeamId() != this->GetGenericTeamId())
    {
        return ETeamAttitude::Hostile;
    }

    return ETeamAttitude::Friendly;
}

void ASRAIController::OnEnemyPerceptionUpdated(AActor *Actor, FAIStimulus Stimulus)
{
    if (Stimulus.WasSuccessfullySensed() && Actor)
    {
        if (UBlackboardComponent *BlackBoard = GetBlackboardComponent())
        {
            BlackBoard->SetValueAsObject(TargetActorBlackBoardValue, Actor);
        }
    }
}

void ASRAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
    checkf(BehaviorTree, TEXT("Behavior Tree of enemy is invalid"));
    RunBehaviorTree(BehaviorTree);
}
