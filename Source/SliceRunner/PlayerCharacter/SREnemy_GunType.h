// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "Interfaces/SRReceiveHitInterface.h"
#include "SREnemy_GunType.generated.h"

class USRAbilitySet;
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
    UPROPERTY(EditDefaultsOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USRAbilitySet> AbilitySet;
};
