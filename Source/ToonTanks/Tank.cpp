// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
  SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
  SpringArm->SetupAttachment(RootComponent);
  
  Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
  PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (PlayerControllerRef)
  {
    FHitResult HitResult;
    PlayerControllerRef->GetHitResultUnderCursor(
      ECollisionChannel::ECC_Visibility,
      false,
      HitResult
    );

    DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 30, 12, FColor::Red);
  }
}

void ATank::BeginPlay()
{
  Super::BeginPlay();

  PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value)
{
  FVector DeltaLocation = FVector::ZeroVector;
  DeltaLocation.X = Value * GetWorld()->GetDeltaSeconds() * MovementSpeed;

  AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
  FRotator DeltaRotation = FRotator::ZeroRotator;
  DeltaRotation.Yaw = Value * GetWorld()->GetDeltaSeconds() * TurnSpeed;

  AddActorLocalRotation(DeltaRotation, true);
}