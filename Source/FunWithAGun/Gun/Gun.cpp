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
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::Shoot(FString ShooterName) {
	UWorld* const World = GetWorld();

	if (World) {
		auto ProjectileSpawnLocation = GunMesh->GetSocketLocation("Projectile");
		auto ProjectileSpawnRotation = GunMesh->GetSocketRotation("Projectile");

		auto Projectile = World->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnLocation, ProjectileSpawnRotation);

		if (Projectile) {
			Projectile->ShooterName = ShooterName;

			Projectile->Launch();
		}
	}
}

