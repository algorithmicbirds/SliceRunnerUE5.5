// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define ECC_Bullet ECC_GameTraceChannel3

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRBulletProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHit, AActor*, OtherActor);

class UNiagaraComponent;
class URadialForceComponent;
class UProjectileMovementComponent;
class UBoxComponent;
class ASREnemy_GunType;

UCLASS()
class SLICERUNNER_API ASRBulletProjectile : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASRBulletProjectile();
    FOnHit OnHit;

protected:
    virtual void BeginPlay() override;
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UNiagaraComponent> NiagaraComponent;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UBoxComponent> ProjectileCollisionComponent;

    UFUNCTION()
    void OnComponentHit(
        UPrimitiveComponent *HitComp,
        AActor *OtherActor,
        UPrimitiveComponent *OtherComp,
        FVector NormalImpulse,
        const FHitResult &Hit
    );
   
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
