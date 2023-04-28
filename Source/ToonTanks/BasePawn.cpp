// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create the capsule component and set it to root
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	// Create the base mesh and set attachment to capsule
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	// Create the turret mesh and set attachment to base mesh
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	// Create the projectile spawn point and set attachment to turret mesh
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	if (DeathParticles)
	{
		// Spawns the death particles when projectile destroys a Pawn
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}
	if (DeathSound)
	{
		// Plays a sound if a pawn is destroyed
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

// Function to rotate turret and projectile spawn point according to mouse location or pawn location
void ABasePawn::RotateTurret(FVector LookAtTarget, float InterpSpeed)
{
	// Find the target of your mouse cursor or pawn from turret mesh
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	// Get DeltaTime
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	// The rotation to move the turret, grabbing only the Yaw.
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	// Call the rotation of the turret mesh based on the mouse or pawn
	TurretMesh->SetWorldRotation(
		// Interpulate the rotation to make it more smooth when looking around
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(), 
			LookAtRotation, 
			DeltaTime,
			InterpSpeed
		)
	);
}

// Fire a projectile from the base pawn
void ABasePawn::Fire()
{
	// Spawn a projectile and grab the variable
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass, 
		ProjectileSpawnPoint->GetComponentLocation(), 
		ProjectileSpawnPoint->GetComponentRotation()
	);
	// Set the projectile owner to this to grab in children classes
	Projectile->SetOwner(this);
}