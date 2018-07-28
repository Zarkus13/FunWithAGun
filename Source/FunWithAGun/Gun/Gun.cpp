// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Gun/Projectile.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>("Root Scene");
	RootScene->SetupAttachment(GetRootComponent());

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>("Gun Mesh");
	GunMesh->SetupAttachment(RootScene);

	GunMesh->SetRelativeRotation(FRotator(0, -270, 270));
	GunMesh->SetRelativeLocation(FVector(-49.5f, 0, -29.45f));
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	DeltaSecondsBetweenShots = 1.f / FiringRate;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsShooting)
		Shoot();
}

void AGun::ToggleShooting() {
	IsShooting = !IsShooting;
}

void AGun::Shoot() {
	UWorld* const World = GetWorld();

	if (World) {
		auto SecondsFromLastShot = World->TimeSeconds - LastShotTime;

		if (SecondsFromLastShot >= DeltaSecondsBetweenShots) {
			auto ProjectileSpawnLocation = GunMesh->GetSocketLocation("Projectile");
			auto ProjectileSpawnRotation = GunMesh->GetSocketRotation("Projectile");

			auto Projectile = World->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnLocation, ProjectileSpawnRotation);

			if (Projectile) {
				Projectile->Shooter = Shooter;
				Projectile->Gun = this;

				Projectile->Launch();

				LastShotTime = World->TimeSeconds;
			}
		}
	}
}



// GETTERS AND SETTERS
void AGun::SetShooter(AActor* Shooter)
{
	this->Shooter = Shooter;
}