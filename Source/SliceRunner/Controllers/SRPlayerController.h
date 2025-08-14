// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "SRPlayerController.generated.h"

/**
 *
 */
UCLASS()
class SLICERUNNER_API ASRPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
    GENERATED_BODY()
public:
    ASRPlayerController();
    virtual FGenericTeamId GetGenericTeamId() const override;

protected:
    FGenericTeamId PlayerTeamID;
};
