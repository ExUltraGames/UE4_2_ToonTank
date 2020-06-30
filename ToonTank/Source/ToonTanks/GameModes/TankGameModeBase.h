// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override; // so GM can get all relevant things at BeginPlay

public:
	
	void ActorDied(AActor* DeadActor); // function player or turret will call on death
	
	//don't implement in Cpp
	UFUNCTION(BlueprintImplementableEvent) // handle all functionality in derived BP i.e. timers , widgets more efficeint in BP
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon); // decide if win or lose state

private:
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
};
