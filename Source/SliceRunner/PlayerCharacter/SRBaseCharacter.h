// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SRBaseCharacter.generated.h"

class USRAbilitySystemComponent;
class USRAbilityManagerComponent;
class USRWeaponBase;

UCLASS()
class SLICERUNNER_API ASRBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASRBaseCharacter();
    USRAbilityManagerComponent* GetAbilityManagerComponent() const;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    TObjectPtr<USRWeaponBase> WeaponMesh;

protected:
    virtual void PossessedBy(AController *NewController) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ablity")
    TObjectPtr<USRAbilityManagerComponent> SRAMC;

};
