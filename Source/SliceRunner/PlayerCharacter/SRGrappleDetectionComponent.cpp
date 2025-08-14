// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter/SRGrappleDetectionComponent.h"
#include "World/GrapplePoint/SRGrapplePoint.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "Debug/DebugHelper.h"

USRGrappleDetectionComponent::USRGrappleDetectionComponent() { PrimaryComponentTick.bCanEverTick = false; }

void USRGrappleDetectionComponent::BeginPlay()
{
    Super::BeginPlay();
    Character = CastChecked<ASRBaseCharacter>(GetOwner());
}

FHitResult USRGrappleDetectionComponent::GetFirstValidGrapplePoint()
{
    if (!Character)
        return FHitResult();

    const FVector Start = Character->GetActorLocation();
    const FVector End = Start + Character->GetControlRotation().Vector() * TraceDistance;

    TArray<FHitResult> OutHits;
    FCollisionQueryParams QueryParam;
    QueryParam.AddIgnoredActor(Character->GetOwner());

    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);
    bool bHit = GetWorld()->SweepMultiByObjectType(
        OutHits, Start, End, FQuat::Identity, ObjectQueryParams, FCollisionShape::MakeSphere(TraceRadius), QueryParam
    );
    //Debug::DrawSweepDebug(GetWorld(), Start, End, TraceRadius, OutHits);

    for (const FHitResult &Hit : OutHits)
    {
        if (Cast<ASRGrapplePoint>(Hit.GetActor()))
        {
            return Hit;
        }
    }

    return FHitResult();
}

void USRGrappleDetectionComponent::CheckForGrapplePoints()
{
    if (GrapplePoint)
    {
        GrapplePoint->SetGrappleIconVisible(false);
        GrapplePoint = nullptr;
    }

    FHitResult Hit = GetFirstValidGrapplePoint();

    if (ASRGrapplePoint *HitPoint = Cast<ASRGrapplePoint>(Hit.GetActor()))
    {
        HitPoint->SetGrappleIconVisible(true);
        GrapplePoint = HitPoint;
    }

    LastGrappleHitResult = Hit;
}

FHitResult USRGrappleDetectionComponent::GetGrappleHitResult() { return LastGrappleHitResult; }

void USRGrappleDetectionComponent::EnableGrappleDetection()
{
    GetWorld()->GetTimerManager().SetTimer(
        GrappleCheckTimerHandle, this, &USRGrappleDetectionComponent::CheckForGrapplePoints, 0.1f, true
    );
}

void USRGrappleDetectionComponent::DisableGrappleDetection()
{
    GetWorld()->GetTimerManager().ClearTimer(GrappleCheckTimerHandle);
}
