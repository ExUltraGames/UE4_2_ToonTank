// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "kismet/GameplayStatics.h" // for FTimer

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true, false); // assign function to a timer
}


// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// will add a general fire function in the Parent class
}

void APawnTurret::CheckFireCondition() // make the AI better / smarter, fire only if this....
{
	//If player == null || if dead then BAIL

	//If player is in range then fire
}
