// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SRGrapplePointWidget.generated.h"

class UImage;
/**
 *
 */
UCLASS()
class SLICERUNNER_API USRGrapplePointWidget : public UUserWidget
{
    GENERATED_BODY()

  protected:
    void NativeConstruct() override;
    UPROPERTY(meta = (BindWidget))
    UImage *GrappleIconAllowed;
    UPROPERTY(meta = (BindWidget))
    UImage *GrappleIconNotAllowed;

    public:
    void SetGrappleIconVisible(bool Visible);
};
