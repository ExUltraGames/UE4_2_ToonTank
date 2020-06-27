// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h" // needed for forward declare

// Sets default values
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
}

void APawnBase::Fire()
{
	//Get ProjectileSpawnPoint Location && Rotation -> Spawn Projectile class at Location towards Rotation
}

void APawnBase::HandleDestruction()
{
	//Individual functionality...
	//Play death effecst Particle, sound and camera shake

	//the do unique child overrides
	// PawnTurret - inform GameMode Turret died -> the Destroy() self

	// PawnTank -  inform GameMode Tank died -> then hide() all components && stop movement input // otherwise lose camera best wat rather than destroy
}

