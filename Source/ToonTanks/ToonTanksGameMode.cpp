// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

    // Cast APawn to ATank which is the child
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    // Makes sure the tank is the dead actor
    if (DeadActor == Tank)
    {
        // Push to the child HandleDestruction in Tank class
        Tank->HandleDestruction();
        // Make sure that it is a player controller
        if (Tank->GetTankPlayerController())
        {
            // Disable input and stop cursor
            Tank->DisableInput(Tank->GetTankPlayerController());
            Tank->GetTankPlayerController()->bShowMouseCursor = false;
        }
    }
    // Checks to see if it's a tower by attempting to cast DeadActor
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        // Push to the child HandleDestruction in the Tower class
        DestroyedTower->HandleDestruction();
    }
}