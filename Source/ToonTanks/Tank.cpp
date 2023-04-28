// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    // Creates SpringArm component and sets the attachment under root
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    // Creates the camera component and sets it under SpringArm
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

    // Gets AController and cast it to the child APlayerController
    TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // Making sure the controller is not null
    if (TankPlayerController)
    {
        // Create HitResult and check for collisions
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, 
            false,
            HitResult
        );
        // Rotate turret every frame following the mouse movement
        RotateTurret(HitResult.ImpactPoint, InterpSpeed);
    }
}

// Handles the destruction of the tank
void ATank::HandleDestruction()
{
    Super::HandleDestruction();

    // Set alive to false
    bAlive = false;
    // Instead of destroying, we hide the pawn and disable tick
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

// Getter for private var TankPlayerController
APlayerController* ATank::GetTankPlayerController() const
{
    return TankPlayerController;
}

// Set up input for pawn to move and fire
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Setting move when a user uses MoveForward
void ATank::Move(float Value)
{
    // Empty DeltaLocation
    FVector DeltaLocation(0,0,0);
    // Grab DeltaTime
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    // Set DeltaLocation X by value passed, speed set and the delta time
    DeltaLocation.X = Value * Speed * DeltaTime;
    // Move the actor in that direction with Sweep
    AddActorLocalOffset(DeltaLocation, true);
}

// Setting move when a user uses Turn
void ATank::Turn(float Value)
{
    // Empty DeltaLocation
    FRotator DeltaRotation = FRotator::ZeroRotator;
    // Grab DeltaTime
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    // Set DeltaLocation Yaw by value passed, speed set and the delta time
    DeltaRotation.Yaw = Value * TurnRate * DeltaTime;
    // Move the actor in that direction with Sweep
    AddActorLocalRotation(DeltaRotation, true);
}