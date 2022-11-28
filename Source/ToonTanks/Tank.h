// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
  ATank();

  // Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  // Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
  virtual void BeginPlay() override;

private:
  UPROPERTY(VisibleAnywhere, Category = "Components")
  class USpringArmComponent* SpringArm;
  UPROPERTY(VisibleAnywhere, Category = "Components")
  class UCameraComponent* Camera;

  void Move(float Value);
  void Turn(float Value);

  APlayerController* PlayerControllerRef;

};
