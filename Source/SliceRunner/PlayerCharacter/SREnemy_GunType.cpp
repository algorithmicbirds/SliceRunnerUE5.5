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
        AIController->TargetDetected.AddDynamic(this, &ASREnemy_GunType::OnTargetDetected);
        AIController->TargetLost.AddDynamic(this, &ASREnemy_GunType::OnTargetLost);
    }
}

void ASREnemy_GunType::BeginPlay()
{
    Super::BeginPlay();
    EnemyAnimInstance = Cast<USREnemyAnimInstance>(GetMesh()->GetAnimInstance());
}

void ASREnemy_GunType::OnTargetDetected(AActor *Actor)
{
    GetWorldTimerManager().SetTimer(LookAtHandle, this, &ASREnemy_GunType::FaceTargetAndPushBack, 0.016f, true);
    TargetActor = Actor;
}

void ASREnemy_GunType::OnTargetLost() { GetWorldTimerManager().ClearTimer(LookAtHandle); }

void ASREnemy_GunType::FaceTargetAndPushBack()
{
    if (TargetActor)
    {
        FVector TargetPosition = TargetActor->GetActorLocation();
        FVector CurrentPosition = GetActorLocation();
        FVector Direction = TargetPosition - CurrentPosition;
        FVector NormalizedDirection = Direction.GetSafeNormal();
        float DistanceToTarget = Direction.Size();

        if (DistanceToTarget < PushBackDist)
        {
            SetActorLocation(CurrentPosition - NormalizedDirection * PushBackSpeed);
        }

        FRotator TargetRotation = FRotationMatrix::MakeFromX(NormalizedDirection).Rotator();
        SetActorRotation(TargetRotation);
        if (EnemyAnimInstance)
        {
            EnemyAnimInstance->SetTargetVisible(true);
            EnemyAnimInstance->SetTargetLocation(TargetActor->GetActorLocation());
        }
        else
        {
            Debug::Print("Enemy anim instance is invalid");
        }
    }
    else
    {
        Debug::Print("Target Actor is invalid");
    }
}
