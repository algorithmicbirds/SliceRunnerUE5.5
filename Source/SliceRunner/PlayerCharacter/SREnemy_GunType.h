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

    UPROPERTY(EditDefaultsOnly, Category = "CharacterData")
    float PushBackDist = 300.0f;

    UPROPERTY(EditDefaultsOnly, Category = "CharacterData")
    float PushBackSpeed = 30.0f;

private:
    UPROPERTY()
    TObjectPtr<ASRAIController> AIController;

    UFUNCTION()
    void OnTargetDetected(AActor *Actor);

    UFUNCTION()
    void OnTargetLost();

    void FaceTargetAndPushBack();

    FTimerHandle LookAtHandle;
    FTimerHandle MoveAwayHandle;

    UPROPERTY()
    AActor *TargetActor = nullptr;

    UPROPERTY()
    TObjectPtr<USREnemyAnimInstance> EnemyAnimInstance;
};
