// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "GameFramework/Pawn.h"
#include "Particles/ParticleSystem.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
  RootComponent = CapsuleComp;

  BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
  BaseMesh->SetupAttachment(CapsuleComp);

  TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
  TurretMesh->SetupAttachment(BaseMesh);

  ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
  ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
  if (DestructionParticles)
  {
    UGameplayStatics::SpawnEmitterAtLocation(this, DestructionParticles, GetActorLocation(), GetActorRotation());
  }
  if (DestructionSound)
  {
    UGameplayStatics::PlaySoundAtLocation(this, DestructionSound, GetActorLocation());
  }

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
  FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
  FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
  
  TurretMesh->SetWorldRotation(FMath::RInterpConstantTo(
    TurretMesh->GetComponentRotation(),
    LookAtRotation,
    GetWorld()->GetDeltaSeconds(),
    TurretRotateSpeed
  ));
}

void ABasePawn::Fire()
{
  AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
    ProjectileClass,
    ProjectileSpawnPoint->GetComponentLocation(),
    ProjectileSpawnPoint->GetComponentRotation()
  );
  Projectile->SetOwner(this);
}

bool ABasePawn::LevelUp(float Exp)
{
  Experience += Exp;

  if (Experience >= RequiredExperience[Level])
  {
    Level++;

    if (LevelUpEffect)
    {
      UGameplayStatics::SpawnEmitterAtLocation(this, LevelUpEffect, GetActorLocation(), GetActorRotation());
    }

    bIsLeveling = true;
    return true;
  }
  return false;
}

void ABasePawn::IncreaseHealth()
{
  if (!bIsLeveling) return;


}

void ABasePawn::IncreaseDamage()
{
  if (!bIsLeveling) return;

  BaseDamage *= 1.2;
  bIsLeveling = false;
}

void ABasePawn::IncreaseFireRate()
{
  if (!bIsLeveling) return;

  FireRate *= 1.15;
  bIsLeveling = false;
}

void ABasePawn::IncreaseFireRange()
{
  if (!bIsLeveling) return;

  FireRange += 100;
  bIsLeveling = false;
}

void ABasePawn::IncreaseProjectileSpeed()
{
  if (!bIsLeveling) return;

  ProjectileSpeed += 200;
  bIsLeveling = false;
}

void ABasePawn::IncreaseMovementSpeed()
{
  if (!bIsLeveling) return;

  MovementSpeed += 50;
  bIsLeveling = false;
}

void ABasePawn::IncreaseTurnSpeed()
{
  if (!bIsLeveling) return;

  TurnSpeed += 10;
  bIsLeveling = false;
}

void ABasePawn::IncreaseTurretTurnSpeed()
{
  if (!bIsLeveling) return;

  TurretRotateSpeed += 15;
  bIsLeveling = false;
  
}

