// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (InActionRange())
  {
    RotateTurret(Tank->GetActorLocation());
  }

}

void ATower::BeginPlay()
{
  Super::BeginPlay();

  Tank = UGameplayStatics::GetPlayerPawn(this, 0);

  GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, 1 / FireRate, true);
}

bool ATower::InActionRange()
{
  if (Tank)
  {
    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
    if (Distance <= FireRange)
    {
      return true;
    }
  }

  return false;
}

void ATower::CheckFireCondition()
{
  if (InActionRange())
  {
    Fire();
  }
}
