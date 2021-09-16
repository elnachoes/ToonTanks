// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

//This is a blank macro to label out parameters for functions.
#define OUTPARAM

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	//Check what kind of actor died. If its the player goto loose condition.
	UE_LOG(LogTemp, Warning, TEXT("A Pawn Died"));

	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);
		
		if (PlayerControllerRef != nullptr)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();

		if (--TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), OUTPARAM TurretActors);
	return TurretActors.Num();
}

void ATankGameModeBase::HandleGameStart()
{
	//Init the start countdown, turret activation, pawn check etc.
	//Call the blueprint version of ATankGameModeBase::GameStart();

	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	if (PlayerControllerRef != nullptr)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);

		//
		FTimerHandle PlayerEnableHandle;

		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);

		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}

	GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	//See if the player has destroyed all the turrets, show win result.
	//else if the turret destroyed the player, show the loose result.
	//Call blueprint version GameOver(bool).

	GameOver(PlayerWon);
}



