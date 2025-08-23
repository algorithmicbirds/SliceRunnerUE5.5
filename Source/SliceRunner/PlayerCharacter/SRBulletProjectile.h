// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRBulletProjectile.generated.h"

class UNiagaraComponent;
class URadialForceComponent;
class UProjectileMovementComponent;

UCLASS()
class SLICERUNNER_API ASRBulletProjectile : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASRBulletProjectile();

protected:
    virtual void BeginPlay() override;
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UNiagaraComponent> NiagaraComponent;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<URadialForceComponent> RadialForceComponent;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
