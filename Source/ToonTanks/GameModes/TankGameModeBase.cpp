// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{
	//Get the references and win/loose conditions.

	//Call HandleGameStart() to init the start countdown, turret activation, pawn check etc. 

}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	//Check what kind of actor died. If its the player goto loose condition.
	UE_LOG(LogTemp, Warning, TEXT("A Pawn Died"));
}

void ATankGameModeBase::HandleGameStart()
{
	//Init the start countdown, turret activation, pawn check etc.
	//Call the blueprint version of ATankGameModeBase::GameStart();
}

void ATankGameModeBase::HandleGameOver()
{
	//See if the player has destroyed all the turrets, show win result.
	//else if the turret destroyed the player, show the loose result.
	//Call blueprint version GameOver(bool).
}



