// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h" // needed for forward declare
#include "Kismet/KismetMathLibrary.h" // for maths calcs

// Sets default values // note if no constructor defined the compile will create it anyway
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent); // inherits properties from root

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	// update turretmesh rotation to face  LookatTarget passed in from child class
	//TurretMesh->SetWorldRotation()...

	//Find Rotation to look at
	FVector StartLocation = TurretMesh->GetComponentLocation();
	FVector TargetLocation = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);// note constructiong an FVector // Don't want to effect .Z no up down
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);

	//RotateTurret
	TurretMesh->SetWorldRotation(TurretRotation);
	//now use in pawnturret class

}

void APawnBase::Fire()
{
	//Get ProjectileSpawnPoint Location && Rotation -> Spawn Projectile class at Location towards Rotation
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
}

void APawnBase::HandleDestruction()
{
	//Individual functionality...
	//Play death effecst Particle, sound and camera shake

	//the do unique child overrides
	// PawnTurret - inform GameMode Turret died -> the Destroy() self

	// PawnTank -  inform GameMode Tank died -> then hide() all components && stop movement input // otherwise lose camera best wat rather than destroy
}

