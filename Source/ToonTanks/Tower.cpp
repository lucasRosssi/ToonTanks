// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (Tank)
  {
    FVector TankLocation = Tank->GetActorLocation();
    float Distance = FVector::Dist(GetActorLocation(), TankLocation);

    if (Distance <= FireRange)
    {
      RotateTurret(TankLocation);
    }
  }

}

void ATower::BeginPlay()
{
  Super::BeginPlay();

  Tank = UGameplayStatics::GetPlayerPawn(this, 0);
}
