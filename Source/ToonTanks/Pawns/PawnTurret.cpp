// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

//Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	//sets up the FireRateTimerHandle to trigger the CheckFireCondition to the time delay in seconds of FireRate
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	//Player 1 is on index 0 
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction()
{
	//Parent function handles partical effect explosion
	Super::HandleDestruction();
	Destroy();


}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	// If player == null || or player == dead

	if (!PlayerPawn)
	{
		return;
	}

	// If player is in range fire

	if (ReturnDistanceToPlayer() <= FireRange)
	{
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.0f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
