// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Setting the current health to max health at the beginning of the game
	CurrentHealth = MaxHealth;
	// Binding the delegate to the DamageTaken function, waiting to see projectile ApplyDamage
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	// Get the game mode and cast it to the child
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	// Make sure there is damage being done
	if (Damage <= 0.f) return;
	// Take the damage from the current health
	CurrentHealth -= Damage;
	// Checking to see if Actor/Pawn is destroyed
	if (CurrentHealth <= 0.f && ToonTanksGameMode) 
	{
		// Push to Game Mode ActorDied() public function
		ToonTanksGameMode->ActorDied(DamagedActor);
	}
}
