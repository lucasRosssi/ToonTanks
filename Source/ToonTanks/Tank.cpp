// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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

  PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
  // PlayerInputComponent->BindAction(TEXT("IncreaseHealth"), IE_Pressed, this, &ABasePawn::IncreaseHealth);
  PlayerInputComponent->BindAction(TEXT("IncreaseDamage"), IE_Pressed, this, &ABasePawn::IncreaseDamage);
  PlayerInputComponent->BindAction(TEXT("IncreaseFireRate"), IE_Pressed, this, &ABasePawn::IncreaseFireRate);
  PlayerInputComponent->BindAction(TEXT("IncreaseFireRange"), IE_Pressed, this, &ABasePawn::IncreaseFireRange);
  PlayerInputComponent->BindAction(TEXT("IncreaseProjectileSpeed"), IE_Pressed, this, &ABasePawn::IncreaseProjectileSpeed);
  PlayerInputComponent->BindAction(TEXT("IncreaseMovementSpeed"), IE_Pressed, this, &ABasePawn::IncreaseMovementSpeed);
  PlayerInputComponent->BindAction(TEXT("IncreaseTurnSpeed"), IE_Pressed, this, &ABasePawn::IncreaseTurnSpeed);
  PlayerInputComponent->BindAction(TEXT("IncreaseTurretTurnSpeed"), IE_Pressed, this, &ABasePawn::IncreaseTurretTurnSpeed);
}

void ATank::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (TankPlayerController)
  {
    FHitResult HitResult;
    TankPlayerController->GetHitResultUnderCursor(
      ECollisionChannel::ECC_Visibility,
      false,
      HitResult
    );

    RotateTurret(HitResult.ImpactPoint);
  }
}

void ATank::HandleDestruction()
{
  Super::HandleDestruction();
  SetActorHiddenInGame(true);
  SetActorTickEnabled(false);
  bTankHidden = true;
  SetActorEnableCollision(false);
}

void ATank::BeginPlay()
{
  Super::BeginPlay();

  TankPlayerController = Cast<APlayerController>(GetController());
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