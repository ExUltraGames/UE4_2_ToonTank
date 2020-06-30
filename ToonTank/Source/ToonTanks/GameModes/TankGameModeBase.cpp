// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	// Get references and game win/lose conditions // variables and conditions
	// Call HandleGameStart() to initialise the start conditions, turret activation, pawn check etc.
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Check what type of actor dies, if turret, tally. if player -> go to lose condition
}

void ATankGameModeBase::HandleGameStart()
{
	//initialise the start conditions, turret activation, pawn check etc.
	// Call BP version GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	//see if player has destroyed all turrest, show Win
	// else if turret destroyed player, show lose
	// Call BP version GameOver();
}
