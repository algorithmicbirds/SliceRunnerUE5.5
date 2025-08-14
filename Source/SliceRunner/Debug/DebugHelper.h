// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h" // For DrawDebug functions

namespace Debug
{
void Print(const FString &Msg, int32 Key = -1, FColor Color = FColor::MakeRandomColor());
void Print(const float &InFloat, int32 Key = -1, FColor Color = FColor::MakeRandomColor());
void Print(const FString &Msg, const float &InFloat, int32 Key = -1, FColor Color = FColor::MakeRandomColor());
void Print(const FVector &InVector, int32 Key = -1, FColor Color = FColor::MakeRandomColor());
void Print(const FString &Msg, const FVector &InVector, int32 Key = -1, FColor Color = FColor::MakeRandomColor());

void DrawSweepDebug(
    UWorld *World,
    const FVector &Start,
    const FVector &End,
    float Radius,
    const TArray<FHitResult> &Hits,
    float Duration = 1.0f
);

void DrawLineDebug(UWorld *World, const FVector &Start, const FVector &End, const FHitResult &Hit, float Duration);
} // namespace Debug
