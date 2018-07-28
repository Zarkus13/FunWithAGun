// Fill out your copyright notice in the Description page of Project Settings.

#include "VRCharacter.h"
#include "Components/ChildActorComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Gun/Gun.h"
#include "UObject/Class.h"


// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>("VRRoot");
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(VRRoot);

	Weapon = CreateDefaultSubobject<UChildActorComponent>("Weapon");
	Weapon->SetupAttachment(VRRoot);
}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto ChildActor = Weapon->GetChildActor();

	Gun = Cast<AGun>(Weapon->GetChildActor());

	if (Gun)
		Gun->SetShooter(this);
}

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto NewCameraOffset = Camera->GetComponentLocation() - GetActorLocation();
	NewCameraOffset.Z = 0;

	AddActorWorldOffset(NewCameraOffset);

	VRRoot->AddWorldOffset(-NewCameraOffset);
}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AVRCharacter::ToggleShooting);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &AVRCharacter::ToggleShooting);
}

void AVRCharacter::ToggleShooting()
{
	if (Gun)
		Gun->ToggleShooting();
}
