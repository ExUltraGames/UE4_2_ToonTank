// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h" // for FTimer

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true, false); // assign function to a timer

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0)); // uses world ref and player index (pawn we are possesing pawn 0)
}



// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//If NO PLayePawn or not in range, return
	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) { return; }
	//If we have a PLayePawn in range the rotate turret to follow
	RotateTurret(PlayerPawn->GetActorLocation()); 

}

void APawnTurret::CheckFireCondition() // make the AI better / smarter, fire only if this....
{
	//If player == null || if dead then BAIL
	if (!PlayerPawn || !PlayerPawn->GetPlayerAlive()) { return; } // check if alive and stop if no player or player dead

	//If player is in range then fire
	// TO DO add don't fire for StartDelay?
	if (ReturnDistanceToPlayer() <= FireRange)
	{
		Fire(); // from parent
	}
}

float APawnTurret::ReturnDistanceToPlayer() // float = use directly in check fire
{	
	//check if we have a valid reference to player
	if (!PlayerPawn) { return 0.0f; } // return false for a float
	float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();// temp variable
	return Distance;
	
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction(); // runs parent logic first then child below...
	Destroy(); //AActor function
}