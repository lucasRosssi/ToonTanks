// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
  if (DeadActor == Tank)
  {
    Tank->HandleDestruction();

    APlayerController* TankPlayerController = Tank->GetTankPlayerController();
    if (ToonTanksPlayerController)
    {
      ToonTanksPlayerController->SetPlayerEnabledState(false);
    }
    GameOver(false);
  }

  if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
  {
    DestroyedTower->HandleDestruction();

    --TargetEnemies;
    if (TargetEnemies == 0)
    {
      GameOver(true);
    }
  }
}

void AToonTanksGameMode::BeginPlay()
{
  Super::BeginPlay();

  HandleGameStart();

}

void AToonTanksGameMode::HandleGameStart()
{
  TargetEnemies = GetTargetEnemiesCount();

  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
  ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

  StartGame();

  if (ToonTanksPlayerController)
  {
    ToonTanksPlayerController->SetPlayerEnabledState(false);

    FTimerHandle PlayerEnableTimerHandle;
    FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
      ToonTanksPlayerController,
      &AToonTanksPlayerController::SetPlayerEnabledState,
      true
    );
    GetWorldTimerManager().SetTimer(
      PlayerEnableTimerHandle,
      PlayerEnableTimerDelegate,
      StartDelay,
      false
    );
  }
}

int32 AToonTanksGameMode::GetTargetEnemiesCount()
{
  TArray<AActor*> Enemies;
  UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Enemies);

  return Enemies.Num();
}
