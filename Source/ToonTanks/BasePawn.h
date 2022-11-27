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

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float MovementSpeed = 400.f;
  UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
  float TurnSpeed = 180.f;
  UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
  float ProjectileSpeed = 1000.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float FireRate = 1.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float BaseDamage = 30.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float Health = 100.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float Shield = 50.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
  UPROPERTY()
  class UCapsuleComponent* CapsuleComp;

  UPROPERTY()
  UStaticMeshComponent* BaseMesh;

  UPROPERTY()
  UStaticMeshComponent* TurretMesh;

  UPROPERTY()
  USceneComponent* ProjectileSpawnPoint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
