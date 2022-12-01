// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Tank.h"

void ATower::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (InActionRange())
  {
    RotateTurret(Tank->GetActorLocation());
  }

}

void ATower::HandleDestruction()
{
  Super::HandleDestruction();
  Destroy();
}

void ATower::BeginPlay()
{
  Super::BeginPlay();

  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

  GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, 1 / FireRate, true);
}

bool ATower::InActionRange()
{
  if (Tank && !Tank->IsTankHidden())
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
