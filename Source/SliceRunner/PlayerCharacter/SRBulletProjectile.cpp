// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter/SRBulletProjectile.h"
#include "NiagaraComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Interfaces/SRReceiveHitInterface.h"
#include "Debug/DebugHelper.h"

// Sets default values
ASRBulletProjectile::ASRBulletProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    ProjectileMovementComponent =
        CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollisionComponent"));
    ProjectileCollisionComponent->SetupAttachment(NiagaraComponent);
    ProjectileCollisionComponent->OnComponentHit.AddDynamic(this, &ASRBulletProjectile::OnComponentHit);

    NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    NiagaraComponent->SetupAttachment(ProjectileCollisionComponent);
}

// Called when the game starts or when spawned
void ASRBulletProjectile::BeginPlay() { Super::BeginPlay(); }

void ASRBulletProjectile::OnComponentHit(
    UPrimitiveComponent *HitComp,
    AActor *OtherActor,
    UPrimitiveComponent *OtherComp,
    FVector NormalImpulse,
    const FHitResult &Hit
)
{
    if (!OtherActor)
    {
        return;
    }

    if (ISRReceiveHitInterface *HitInterfece = Cast<ISRReceiveHitInterface>(OtherActor))
    {
        HitInterfece->RecieveHitEvent();
    }
    Destroy();
}

// Called every frame
void ASRBulletProjectile::Tick(float DeltaTime) { Super::Tick(DeltaTime); }
