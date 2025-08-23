// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter/SRBulletProjectile.h"
#include "NiagaraComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ASRBulletProjectile::ASRBulletProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
    RadialForceComponent->SetupAttachment(NiagaraComponent);

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

// Called when the game starts or when spawned
void ASRBulletProjectile::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void ASRBulletProjectile::Tick(float DeltaTime) { Super::Tick(DeltaTime); }
