// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

  void HandleDestruction();
  bool LevelUp(float Exp);

  bool bIsLeveling = false;
  void IncreaseHealth();
  void IncreaseDamage();
  void IncreaseFireRate();
  void IncreaseFireRange();
  void IncreaseProjectileSpeed();
  void IncreaseMovementSpeed();
  void IncreaseTurnSpeed();
  void IncreaseTurretTurnSpeed();

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecialStats")
  float MovementSpeed = 400.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecialStats")
  float TurnSpeed = 70.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecialStats")
  float TurretRotateSpeed = 90.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecialStats")
  float ProjectileSpeed = 1000.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecialStats")
  float FireRange = 500.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecialStats")
  float FireRate = 1.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecialStats")
  float BaseDamage = 30.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
  float Experience = 0;
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
  int32 Level = 1;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
  float ExperienceOnDeath;

protected:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  class UCapsuleComponent* CapsuleComp;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  UStaticMeshComponent* BaseMesh;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  UStaticMeshComponent* TurretMesh;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  USceneComponent* ProjectileSpawnPoint;
  UPROPERTY(EditAnywhere, Category = "Destruction")
  class UParticleSystem* DestructionParticles;

  UPROPERTY(EditAnywhere, Category = "Destruction")
  class USoundBase* DestructionSound;

  UPROPERTY(EditDefaultsOnly, Category = "Level")
  UParticleSystem* LevelUpEffect;

  void RotateTurret(FVector LookAtTarget);
  void Fire();

private:
  UPROPERTY(EditDefaultsOnly, Category = "Combat")
  TSubclassOf<class AProjectile> ProjectileClass;


  TArray<float> RequiredExperience = { 0, 50, 125, 225, 350, 500, 700, 1000, 1425, 2000 };
 
};
