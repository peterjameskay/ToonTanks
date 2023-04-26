// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"


void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Checks to see if tank is in fire range
    if (InFireRange())
    {
        // Rotates turret to Tank based on location
        RotateTurret(Tank->GetActorLocation(), InterpSpeed);
    }
}

// Handles the destruction of a Tower
void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    
    // Cast APawn to ATank which is the child
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    // Timer set to fire projectiles
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    // Checks to see if target is in fire range
    if (InFireRange())
    {
        // Fire's projectile
        Fire();
    }
}

bool ATower::InFireRange()
{
    // Checks to see if Tank is not null
    if (Tank) {
        // Get the distance between tower and tank
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        // Return bool based on distance and fire range
        return Distance <= FireRange;
    }
    // Return false if Tank is null
    return false;
}