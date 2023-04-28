// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"


UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Finds where to send the DeadActor based on ABasePawn children
	void ActorDied(AActor* DeadActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Start Game is called in BeginPlay to use for Blueprint
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	// Game Over is called in ActorDied to use for Blueprint
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	// Variables
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	UPROPERTY(EditAnywhere)
	float StartDelay = 4.f;

	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();

	void HandleGameStart();
};
