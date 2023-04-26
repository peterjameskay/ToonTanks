// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"


UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	// Handles the destruction of a Tower
	void HandleDestruction();

protected:
	virtual void BeginPlay() override;

private:
	// Variables
	class ATank* Tank; 
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 300.f;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float InterpSpeed = 10.f;
	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;

	// Functions
	void CheckFireCondition();
	bool InFireRange();
};