// Fill out your copyright notice in the Description page of Project Settings.

#include "World/GrapplePoint/SRGrapplePoint.h"
#include "World/GrapplePoint/SRGrapplePointWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASRGrapplePoint::ASRGrapplePoint()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
    WidgetComponent->SetupAttachment(RootComponent);
    WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
    WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    WidgetComponent->SetPivot(FVector2D(0.5f, 0.5f));
}

// Called when the game starts or when spawned
void ASRGrapplePoint::BeginPlay() { 
    Super::BeginPlay();

}

void ASRGrapplePoint::SetGrappleIconVisible(bool Visible)
{
    if (UUserWidget *Widget = WidgetComponent->GetUserWidgetObject())
    {
        USRGrapplePointWidget *GrappleWidget = Cast<USRGrapplePointWidget>(Widget);
        if (GrappleWidget)
        {
            GrappleWidget->SetGrappleIconVisible(Visible);
        }
    }
}

// Called every frame
void ASRGrapplePoint::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APlayerCameraManager *CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
    if (!CameraManager || !WidgetComponent)
        return;

    FVector ToCamera = CameraManager->GetCameraLocation() - WidgetComponent->GetComponentLocation();
    FRotator LookAtRotation = FRotationMatrix::MakeFromX(ToCamera).Rotator();

    LookAtRotation.Pitch = 0.f;
    LookAtRotation.Roll = 0.f;

    WidgetComponent->SetWorldRotation(LookAtRotation);
}
