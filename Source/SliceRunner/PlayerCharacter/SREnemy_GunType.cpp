// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter/SREnemy_GunType.h"
#include "AbilitySystem/SRAbilityManagerComponent.h"
#include "GameplayTags/SRGameplayTags.h"
#include "Debug/DebugHelper.h"
#include "AbilitySystem/SRAbilitySet.h"
#include "Controllers/SRAIController.h"
#include "AnimInstance/Enemy/SREnemyAnimInstance.h"

ASREnemy_GunType::ASREnemy_GunType() {}

void ASREnemy_GunType::RecieveHitEvent()
{
    if (SRAMC)
    {
        SRAMC->StartAbilityByTag(SRGameplayTags::AbilityTag_Death);
    }
}

void ASREnemy_GunType::PossessedBy(AController *NewController)
{
    Super::PossessedBy(NewController);
    checkf(AbilitySet, TEXT("Forgot to assign Ability Set To Enemy Gun Type"));
    if (SRAMC)
    {
        AbilitySet->GiveAbilityToManager(SRAMC);
    }
    AIController = Cast<ASRAIController>(NewController);
    if (AIController)
    {
        AIController->PlayerDetected.AddDynamic(this, &ASREnemy_GunType::OnPlayerDetected);
        AIController->PlayerLost.AddDynamic(this, &ASREnemy_GunType::OnPlayerLost);
    }
}

void ASREnemy_GunType::BeginPlay()
{
    Super::BeginPlay();
    EnemyAnimInstance = Cast<USREnemyAnimInstance>(GetMesh()->GetAnimInstance());
}

void ASREnemy_GunType::OnPlayerDetected(AActor *Actor)
{
    GetWorld()->GetTimerManager().SetTimer(LookAtHandle, this, &ASREnemy_GunType::LookAt, 0.016f, true);
    PlayerCharacter = Actor;
}

void ASREnemy_GunType::OnPlayerLost()
{
    GetWorld()->GetTimerManager().ClearTimer(LookAtHandle);
    EnemyAnimInstance->SetTargetVisible(false);
}

void ASREnemy_GunType::LookAt()
{
    if (EnemyAnimInstance)
    {
        EnemyAnimInstance->SetTargetVisible(true);
        EnemyAnimInstance->SetTargetLocation(PlayerCharacter->GetActorLocation());
    }
    else
    {
        Debug::Print("We are sorry to inform enemy anim instance is invalid");
    }
}
