// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter/SRWallRunComponent.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


USRWallRunComponent::USRWallRunComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USRWallRunComponent::BeginPlay() { Character = CastChecked<ASRBaseCharacter>(GetOwner()); }


bool USRWallRunComponent::CheckForWall(const FHitResult &Hit)
{
    if (!Character)
    {
        return false;
    }
    float CharacterAndWallAlignment =
        FMath::Abs(FVector::DotProduct(Hit.ImpactNormal, Character->GetActorRightVector()));
    return CharacterAndWallAlignment > 0.7f;
}

void USRWallRunComponent::StartWallRun(const FHitResult &Hit)
{
    if (!Character || bIsWallRunning)
    {
        return;
    }
    bIsWallRunning = true;
    if (Character->GetCharacterMovement()->IsFalling())
    {
        Character->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
        Character->GetCharacterMovement()->SetPlaneConstraintEnabled(true);
        Character->GetCharacterMovement()->SetPlaneConstraintNormal(Hit.ImpactNormal);
    }

    GetWorld()->GetTimerManager().SetTimer(
        WallRunCheckTimerHandle, this, &USRWallRunComponent::EvaluateWallRunStateWithWallChecks, 0.1f, true
    );
    GetWorld()->GetTimerManager().SetTimer(
        WallRunMovementCheckHandle, this, &USRWallRunComponent::CheckWallRunEndDueToNoMovement, 0.1f, true
    );
}

void USRWallRunComponent::StopWallRun()
{
    if (!Character)
    {
        return;
    }
    bIsWallRunning = false;
    Character->GetCharacterMovement()->SetPlaneConstraintEnabled(false);
    Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
    GetWorld()->GetTimerManager().ClearTimer(WallRunCheckTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(WallRunMovementCheckHandle);
}


void USRWallRunComponent::EvaluateWallRunStateWithWallChecks()
{
    if (!bIsWallRunning || !Character)
    {
        return;
    }

    float CastLength = 100.0f;
    FVector CharacterRightVector = Character->GetActorRightVector();

    bool bIsRightClear = !PerformRayCast(CharacterRightVector, CastLength);
    bool bIsLeftClear = !PerformRayCast(-CharacterRightVector, CastLength);

    if (bIsRightClear && bIsLeftClear && bIsWallRunning)
    {
        StopWallRun();
    }
}

void USRWallRunComponent::CheckWallRunEndDueToNoMovement()
{
    if (!bIsWallRunning || !Character)
    {
        return;
    }

    if (Character->GetCharacterMovement()->GetCurrentAcceleration().IsNearlyZero())
    {
        StopWallRun();
    }
}

bool USRWallRunComponent::PerformRayCast(FVector CastDirection, float CastLength)
{
    FHitResult HitInfo;
    if (!Character)
    {
        return false;
    }
    FVector Origin = Character->GetActorLocation();
    FVector EndPosition = Origin + CastDirection * CastLength;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Character);

    bool rayHit = GetWorld()->LineTraceSingleByChannel(
        HitInfo, Origin, EndPosition, ECC_GameTraceChannel1, Params, FCollisionResponseParams()
    );
    return rayHit;
}
