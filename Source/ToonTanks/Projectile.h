// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
  UStaticMeshComponent* ProjectileMesh;
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
  class UProjectileMovementComponent* ProjectileMovementComponent;

  UPROPERTY(VisibleAnywhere, Category = "Movement")
  class UParticleSystemComponent* TrailParticlesComponent;

  UPROPERTY(EditAnywhere, Category = "Combat")
  USoundBase* FireSound;
  UPROPERTY(EditAnywhere, Category = "Combat")
  USoundBase* HitSound;

  UPROPERTY(EditAnywhere, Category = "Combat")
  TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
  UFUNCTION()
  void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

  UPROPERTY(EditAnywhere, Category = "Combat")
  float Damage = 50.f;
  UPROPERTY(EditAnywhere, Category = "Combat")
  float Range = 500.f;

  FVector StartingPoint;

  UPROPERTY(EditAnywhere, Category = "Combat")
  UParticleSystem* HitParticles;


};
