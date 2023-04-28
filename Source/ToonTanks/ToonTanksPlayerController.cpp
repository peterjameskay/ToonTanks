// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled){

    // Checks to see if player is enabled
    if (bPlayerEnabled) {
        GetPawn()->EnableInput(this);
    }
    else 
    {
        GetPawn()->DisableInput(this);
    }

    // Setting to see the cursor based on if player ie enabled
    bShowMouseCursor = bPlayerEnabled;
}