// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter/SREnemy_GunType.h"
#include "AbilitySystem/SRAbilityManagerComponent.h"
#include "GameplayTags/SRGameplayTags.h"
#include "Debug/DebugHelper.h"
#include "AbilitySystem/SRAbilitySet.h"
#include "Controllers/SRAIController.h"
#include "AnimInstance/Enemy/SREnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

ASREnemy_GunType::ASREnemy_GunType()
{
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.bCanEverTick = true;
}

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

void ASREnemy_GunType::Tick(float DeltaTime) { 
    if (bIsTargetInRange)
    {
        FaceTargetAndPushBack();
    }
}

void ASREnemy_GunType::OnTargetDetected(AActor *Actor)
{
    bIsTargetInRange = true;
    TargetActor = Actor;
    GetWorldTimerManager().SetTimer(ShootHandle, this, &ASREnemy_GunType::Shoot, 0.1f, true);
}

void ASREnemy_GunType::OnTargetLost()
{
    bIsTargetInRange = false;
    GetWorldTimerManager().ClearTimer(ShootHandle);
    if (EnemyAnimInstance)
    {
        EnemyAnimInstance->SetTargetVisible(false);
    }
}

void ASREnemy_GunType::FaceTargetAndPushBack()
{
    if (!TargetActor || !EnemyAnimInstance)
    {
        Debug::Print("Target Actor or Enemy Anim Instance is invalid");
        return;
    }

    FVector TargetPosition = TargetActor->GetActorLocation();
    FVector CurrentPosition = GetActorLocation();
    FVector Direction = TargetPosition - CurrentPosition;
    FVector NormalizedDirection = Direction.GetSafeNormal();
    float DistanceToTarget = Direction.Size();

    if (DistanceToTarget < PushBackDist)
    {
        EnemyAnimInstance->SetIsMovingAwayFromTarget(true);
        PushBackSpeed = GetCharacterMovement()->GetMaxSpeed();
        AddMovementInput(-NormalizedDirection, PushBackSpeed);
    }
    else
    {
        EnemyAnimInstance->SetIsMovingAwayFromTarget(false);
    }

    // Rotate Enemy to face the  Target if vertical angle is within allowed constraints
    // Prevents Enemy from tilting whole body upwards when target is airborne
    if (NormalizedDirection.Z <= MaxVerticalRotationZ)
    {
        FRotator TargetRotation = FRotationMatrix::MakeFromX(NormalizedDirection).Rotator();
        SetActorRotation(TargetRotation);
    }

    EnemyAnimInstance->SetTargetLocation(TargetActor->GetActorLocation());
    EnemyAnimInstance->SetTargetVisible(true);
}

void ASREnemy_GunType::Shoot() {}
