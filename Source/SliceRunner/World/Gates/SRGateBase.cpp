// Fill out your copyright notice in the Description page of Project Settings.

#include "World/Gates/SRGateBase.h"
#include "Components/BoxComponent.h"
#include "Debug/DebugHelper.h"


// Sets default values
ASRGateBase::ASRGateBase()
{
    PrimaryActorTick.bCanEverTick = false;

    GateTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
    RootComponent = GateTrigger;

    GateTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    GateTrigger->SetCollisionObjectType(ECC_WorldStatic);
    GateTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
    GateTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    GateTrigger->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ASRGateBase::BeginPlay()
{
    Super::BeginPlay();
    GateTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASRGateBase::OnOverlapBegin);
}

// Called every frame
void ASRGateBase::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

const FGateAbilityFlags &ASRGateBase::GetGateAbilities() const { return AbilityFlags; }


void ASRGateBase::OnOverlapBegin(
    UPrimitiveComponent *OverlappedComp,
    AActor *OtherActor,
    UPrimitiveComponent *OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult &SweepResult
)
{
    if (!OtherActor || OtherActor == this)
        return;

    if (IGateRuleInterface *GateRuleInterface = Cast<IGateRuleInterface>(OtherActor))
    {
        const FGateAbilityFlags &GateFlags = GetGateAbilities();
        GateRuleInterface->SetAbilityFlags(GateFlags);
    }
}
