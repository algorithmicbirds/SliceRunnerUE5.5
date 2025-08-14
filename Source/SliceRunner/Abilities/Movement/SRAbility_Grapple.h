// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SRAbilityBase.h"
#include "SRAbility_Grapple.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class ASRBaseCharacter;
class ASRGrapplePoint;

UCLASS()
class SLICERUNNER_API USRAbility_Grapple : public USRAbilityBase
{
    GENERATED_BODY()

  public:
    USRAbility_Grapple();


  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Grapple")
    UNiagaraSystem *GrappleBeamFX;

    UPROPERTY(EditDefaultsOnly, Category = "Grapple")
    FName GrappleStartSocketName = TEXT("grapple_socket");

    UPROPERTY(EditDefaultsOnly, Category = "Grapple")
    float GrappleSpeed = 2500.0f;

    FTimerHandle UpdateGrappleMovementTimerHandle;
    UPROPERTY(BlueprintReadOnly, Category = "Grapple")
    FVector CurrentGrappleTarget;
    

    UPROPERTY()
    TObjectPtr<ASRBaseCharacter> Character = nullptr;
 
    UPROPERTY()
    TObjectPtr<UNiagaraComponent> ActiveBeamFX = nullptr;
    virtual void ActivateAbility(const FSRAbilityActivationContext &Context) override;
    virtual void EndAbility() override;

    void Grapple(const FHitResult &HitResult);
    void UpdateGrappleMovement();
    void ResetGrappleState();
    void SpawnBeamEffect(const FVector &Target);
    void DestroyBeamEffect();
};
