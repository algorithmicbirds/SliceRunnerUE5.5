// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SRGrappleDetectionComponent.generated.h"

class ASRGrapplePoint;
class ASRBaseCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class USRGrappleDetectionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USRGrappleDetectionComponent();

protected:
    virtual void BeginPlay() override;

    FHitResult GetFirstValidGrapplePoint();
    void CheckForGrapplePoints();

    UPROPERTY()
    TObjectPtr<ASRGrapplePoint> GrapplePoint = nullptr;

    UPROPERTY()
    TObjectPtr<ASRBaseCharacter> Character = nullptr;
    FTimerHandle GrappleCheckTimerHandle;
    FHitResult LastGrappleHitResult;

    UPROPERTY(EditDefaultsOnly, Category = "Grapple Detection")
    float TraceRadius = 50.0f;
    UPROPERTY(EditDefaultsOnly, Category = "Grapple Detection")
    float TraceDistance = 1200.0f;

public:
    FHitResult GetGrappleHitResult();
    void EnableGrappleDetection();
    void DisableGrappleDetection();
};
