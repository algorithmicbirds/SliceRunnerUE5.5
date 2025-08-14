#include "Debug/DebugHelper.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"

namespace Debug
{
template <typename T> void PrintHelper(const T &Msg, int32 Key, FColor Color)
{
    if (GEngine)
    {
        const FString DebugString = Msg;
        GEngine->AddOnScreenDebugMessage(Key, 5.0f, Color, DebugString);

        UE_LOG(LogTemp, Warning, TEXT("%s"), *DebugString);
    }
}

void Print(const FString &Msg, int32 Key, FColor Color) { PrintHelper(Msg, Key, Color); }

void Print(const float &InFloat, int32 Key, FColor Color)
{
    const FString DebugString = FString::Printf(TEXT("%.2f"), InFloat);
    PrintHelper(DebugString, Key, Color);
}

void Print(const FString &Msg, const float &InFloat, int32 Key, FColor Color)
{
    const FString DebugString = FString::Printf(TEXT("%s : %.2f"), *Msg, InFloat);
    PrintHelper(DebugString, Key, Color);
}

void Print(const FVector &InVector, int32 Key, FColor Color)
{
    const FString DebugString =
        FString::Printf(TEXT("Vector: X=%.2f Y=%.2f Z=%.2f"), InVector.X, InVector.Y, InVector.Z);
    PrintHelper(DebugString, Key, Color);
}

void Print(const FString &Msg, const FVector &InVector, int32 Key, FColor Color)
{
    const FString DebugString =
        FString::Printf(TEXT("%s Vector: X=%.2f Y=%.2f Z=%.2f"), *Msg, InVector.X, InVector.Y, InVector.Z);
    PrintHelper(DebugString, Key, Color);
}

void DrawSweepDebug(
    UWorld *World,
    const FVector &Start,
    const FVector &End,
    float Radius,
    const TArray<FHitResult> &Hits,
    float Duration
)
{
    if (!World)
        return;

    DrawDebugSphere(World, End, Radius, 12, FColor::Red, false, Duration);
    DrawDebugLine(World, Start, End, FColor::Red, false, Duration, 0, 5.0f);

    for (const FHitResult &Hit : Hits)
    {
        DrawDebugLine(World, Start, Hit.ImpactPoint, FColor::Yellow, false, Duration, 0, 5.0f);
        DrawDebugSphere(World, Hit.ImpactPoint, Radius * 1.5f, 12, FColor::Yellow, false, Duration);

        UE_LOG(
            LogTemp, Log, TEXT("Hit at: X=%.2f Y=%.2f Z=%.2f"), Hit.ImpactPoint.X, Hit.ImpactPoint.Y, Hit.ImpactPoint.Z
        );
    }
}

void DrawLineDebug(UWorld *World, const FVector &Start, const FVector &End, const FHitResult &Hit, float Duration)
{
    if (!World)
        return;

    DrawDebugLine(World, Start, End, FColor::Red, false, Duration, 0, 2.0f);

    if (Hit.bBlockingHit)
    {
        DrawDebugLine(World, Start, Hit.ImpactPoint, FColor::Yellow, false, Duration, 0, 2.0f);
        DrawDebugSphere(World, Hit.ImpactPoint, 10.0f, 12, FColor::Yellow, false, Duration);

        UE_LOG(
            LogTemp, Log, TEXT("Hit at: X=%.2f Y=%.2f Z=%.2f"), Hit.ImpactPoint.X, Hit.ImpactPoint.Y, Hit.ImpactPoint.Z
        );
    }
}
} // namespace Debug
