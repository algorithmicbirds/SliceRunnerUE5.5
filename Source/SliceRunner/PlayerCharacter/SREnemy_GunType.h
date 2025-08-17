// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "Interfaces/SRReceiveHitInterface.h"
#include "SREnemy_GunType.generated.h"

class USRAbilitySet;
class ASRAIController;
class USREnemyAnimInstance;
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
    UPROPERTY(EditDefaultsOnly, Category = "CharacterData")
    TObjectPtr<USRAbilitySet> AbilitySet;

private:
    UPROPERTY()
    TObjectPtr<ASRAIController> AIController;

    UFUNCTION()
    void OnPlayerDetected(AActor* Actor);

    UFUNCTION()
    void OnPlayerLost();

    void LookAt();

    FTimerHandle LookAtHandle;

    UPROPERTY()
    AActor *PlayerCharacter = nullptr;

    UPROPERTY()
    TObjectPtr<USREnemyAnimInstance> EnemyAnimInstance;
};
