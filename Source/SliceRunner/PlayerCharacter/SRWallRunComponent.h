// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SRWallRunComponent.generated.h"

class ASRBaseCharacter;
/**
 *
 */
UCLASS()
class SLICERUNNER_API USRWallRunComponent : public UActorComponent
{
    GENERATED_BODY()

    USRWallRunComponent();

public:
    void StartWallRun(const FHitResult &Hit);
    void StopWallRun();
    bool CheckForWall(const FHitResult &Hit);
    bool IsWallRunning() const { return bIsWallRunning; }

protected:
    virtual void BeginPlay() override;
    void EvaluateWallRunStateWithWallChecks();
    void CheckWallRunEndDueToNoMovement();
    bool PerformRayCast(FVector CastDirection, float CastLength);
    bool bIsWallRunning = false;
    FTimerHandle WallRunCheckTimerHandle;
    FTimerHandle WallRunMovementCheckHandle;
    UPROPERTY()
    TObjectPtr<ASRBaseCharacter> Character = nullptr;
};
