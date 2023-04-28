// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

    // Sets up the game
    HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    // Makes sure the tank is the dead actor
    if (DeadActor == Tank)
    {
        // Push to the child HandleDestruction in Tank class
        Tank->HandleDestruction();
        // Make sure that it is a player controller
        if (ToonTanksPlayerController)
        {
            // Disable input and stop cursor by calling SetPlayerEnabledState()
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
    }
    // Checks to see if it's a tower by attempting to cast DeadActor
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        // Push to the child HandleDestruction in the Tower class
        DestroyedTower->HandleDestruction();
    }
}

void AToonTanksGameMode::HandleGameStart()
{
    // Cast APawn to ATank which is the child
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    // Cast APlayerController to AToonTanksPlayerController
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();
    // Checks to see player controller is not null
    if (ToonTanksPlayerController)
    {
        // Disable input and stop cursor by calling SetPlayerEnabledState()
        ToonTanksPlayerController->SetPlayerEnabledState(false);
        // Create timer handle
        FTimerHandle PlayerEnableTimerHandle;
        // Creates the delegate for enabling state after timer is finised
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController, 
            &AToonTanksPlayerController::SetPlayerEnabledState, 
            true
        );
        // Sets the timer based on StartDelay variable, after timer the delegate enables input and cursor
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
    }

}