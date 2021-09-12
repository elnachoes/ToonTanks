// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	void HandleGameStart();
	void HandleGameOver();


public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	//These functions will be implemented in blueprints only and NOT in the CPP file.
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

};
