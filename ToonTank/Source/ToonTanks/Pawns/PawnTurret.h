// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank; // needed to create a ref to Tank so we don't check every frame // IWYU

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f; // how often FTimer should tick i.e 2 seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.0f;
	
	APawnTank* PlayerPawn;
	FTimerHandle FireRateTimerHandle; // for FTimer

	void CheckFireCondition();
	float ReturnDistanceToPlayer();

protected: 

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleDestruction() override; // implementing from parent but adding additional logic
	
};
