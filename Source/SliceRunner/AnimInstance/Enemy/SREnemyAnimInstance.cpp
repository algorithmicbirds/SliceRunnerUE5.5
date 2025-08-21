// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/Enemy/SREnemyAnimInstance.h"
#include "PlayerCharacter/SRBaseCharacter.h"



void USREnemyAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
    if (!Character)
    {
        return;
    }
    Direction = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
}
