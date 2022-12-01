// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
  if (DeadActor == Tank)
  {
    Tank->HandleDestruction();

    APlayerController* TankPlayerController = Tank->GetTankPlayerController();
    if (TankPlayerController)
    {
      Tank->DisableInput(TankPlayerController);
      TankPlayerController->bShowMouseCursor = false;
    }
  }

  if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
  {
    DestroyedTower->HandleDestruction();
  }
}

void AToonTanksGameMode::BeginPlay()
{
  Super::BeginPlay();

  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}