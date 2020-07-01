// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTurret.h" 
#include "ToonTanks/Pawns/PawnTank.h" 
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h" 
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATankGameModeBase::BeginPlay()
{
	//turrets player will face
	TargetTurrets = GetTargetTurretCount();
	// get player variable reference
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	// can use to control whether player input is received at certian elements of game i.e. ActorDied
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart();

	Super::BeginPlay();
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TSubclassOf<APawnTurret> ClassToFind;
	ClassToFind = APawnTurret::StaticClass();// returns UClass Object of APawnTurret
	TArray<AActor*> TurretActors; // array of pointers to all turrets in level
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TurretActors);// fill array with actors of this class in world
	return TurretActors.Num();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		// tell pawnclass to handle death
		PlayerTank->PawnDestroyed();
		HandleGameOver(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))// if cast successful actor of type APawnTurret
	{	//by doing this way we get a ref to Turret which we use below
		DestroyedTurret->PawnDestroyed();
		TargetTurrets--;

		if (TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}
}

void ATankGameModeBase::HandleGameStart()
{
	//initialise the start conditions, turret activation, pawn check etc.
	// Call BP version GameStart();
	GameStart();

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);

		// need timer to enable // similar to APawnTurret timer
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// see if player has destroyed all turrest, show Win
	// else if turret destroyed player, show lose
	// Call BP version GameOver();
	GameOver(PlayerWon);
}
