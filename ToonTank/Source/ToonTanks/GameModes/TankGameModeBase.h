// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
class APawnTank;
class APlayerControllerBase;//IWYU

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
	int32 TargetTurrets = 0; // number of turrets to destroy
	
	APlayerControllerBase* PlayerControllerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Loop", meta = (AllowPrivateAccess = "true"))
	int StartDelay = 3; // int not int32 as BP can't deal with that
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	APawnTank* PlayerTank;

	int32 GetTargetTurretCount();
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
};
