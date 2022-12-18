// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
  RootComponent = ProjectileMesh;
  ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
  ProjectileMovementComponent->MaxSpeed = 1000.f;
  ProjectileMovementComponent->InitialSpeed = 1000.f;

  TrailParticlesComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailParticlesComponent"));
  TrailParticlesComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
  StartingPoint = GetActorLocation();
	
  ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

  if (FireSound)
    {
      UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
    }
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  float DistanceTravelled = FVector::Distance(StartingPoint, GetActorLocation());
  if (DistanceTravelled >= Range)
  {
    if (HitParticles)
      {
        UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
      }
    Destroy();
  }

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
  AActor* MyOwner = GetOwner();
  if (!MyOwner)
  {
    Destroy();
    return;
  }

  AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
  UClass* DamageTypeClass = UDamageType::StaticClass();

  if (OtherActor && OtherActor != this && OtherActor != MyOwner)
  {
    UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
    if (HitParticles)
    {
      UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
    }
    if (HitSound && OtherActor->GetNetOwningPlayer())
    {
      UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
    }
    if (HitCameraShakeClass && OtherActor->GetNetOwningPlayer())
    {
      GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
    }
  }

  Destroy();

}
