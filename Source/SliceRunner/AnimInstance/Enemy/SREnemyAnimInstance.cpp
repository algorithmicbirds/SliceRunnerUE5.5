// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstance/Enemy/SREnemyAnimInstance.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "KismetAnimationLibrary.h"

void USREnemyAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
    if (!Character)
    {
        return;
    }
    Direction = UKismetAnimationLibrary::CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
}
