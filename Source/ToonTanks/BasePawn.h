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

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecialStats")
  float MovementSpeed = 400.f;
  UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SpecialStats")
  float TurnSpeed = 75.f;
  UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SpecialStats")
  float ProjectileSpeed = 1000.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecialStats")
  float FireRate = 1.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecialStats")
  float BaseDamage = 30.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecialStats")
  float Health = 100.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecialStats")
  float Shield = 50.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  class UCapsuleComponent* CapsuleComp;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  UStaticMeshComponent* BaseMesh;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  UStaticMeshComponent* TurretMesh;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
  USceneComponent* ProjectileSpawnPoint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
