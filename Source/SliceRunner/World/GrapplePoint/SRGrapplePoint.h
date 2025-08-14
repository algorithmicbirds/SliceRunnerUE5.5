// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRGrapplePoint.generated.h"

class UWidgetComponent;
class USRGrapplePointWidget;

UCLASS()
class SLICERUNNER_API ASRGrapplePoint : public AActor
{
    GENERATED_BODY()

  public:
    // Sets default values for this actor's properties
    ASRGrapplePoint();

  protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

   void SetGrappleIconVisible(bool Visible);
  private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UWidgetComponent *WidgetComponent;
};
