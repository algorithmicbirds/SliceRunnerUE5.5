// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SRAIPreception.generated.h"

USTRUCT()
struct FSRAIPreceptionConfig
{
    GENERATED_BODY()

public:
    float radius;
    float angle;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SLICERUNNER_API USRAIPreception : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    USRAIPreception();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void
    TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:
    
    UPROPERTY()
    TObjectPtr<AActor> Actor;
};
