// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "Interfaces/SRReceiveHitInterface.h"
#include "SREnemy_GunType.generated.h"

class USRAbilitySet;
class ASRAIController;
class USREnemyAnimInstance;
class ASRBulletProjectile;

/**
 *
 */
UCLASS()
class SLICERUNNER_API ASREnemy_GunType : public ASRBaseCharacter, public ISRReceiveHitInterface
{
    GENERATED_BODY()
public:
    ASREnemy_GunType();

protected:
    virtual void RecieveHitEvent() override;
    virtual void PossessedBy(AController *NewController) override;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    UPROPERTY(EditDefaultsOnly, Category = "EnemyData")
    TObjectPtr<USRAbilitySet> AbilitySet;

    UPROPERTY(EditDefaultsOnly, Category = "EnemyData")
    TSubclassOf<ASRBulletProjectile> BulletProjectileClass;

    UPROPERTY(EditDefaultsOnly, Category = "EnemyData")
    FName ProjectileSpawnSocketName = "projectile_socket";

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    float PushBackDist = 300.0f;

private:
    UPROPERTY()
    TObjectPtr<ASRAIController> AIController;

    UFUNCTION()
    void OnTargetDetected(AActor *Actor);

    UFUNCTION()
    void OnTargetLost();

    void FaceTargetAndPushBack(float DeltaTime);
    void Shoot();

    FTimerHandle ShootHandle;

    UPROPERTY()
    AActor *TargetActor = nullptr;

    UPROPERTY()
    TObjectPtr<USREnemyAnimInstance> EnemyAnimInstance;

    bool bIsTargetInRange = false;

    float ShootInterVal = 0.1f;
    float TimeSinceLastShot = 0.0f;
};
