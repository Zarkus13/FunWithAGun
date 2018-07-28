// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class FUNWITHAGUN_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void ToggleShooting();

	void SetShooter(class AActor* Shooter);

	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	class USceneComponent* RootScene = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	class UStaticMeshComponent* GunMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileClass = nullptr;

private:
	FString ShooterName;
	class AActor* Shooter;

	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	float FiringRate = 5;

	float DeltaSecondsBetweenShots = 0;

	float LastShotTime = 0.f;
	bool IsShooting = false;
};
