// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // NO TICK

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh; // inherits properties from root

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement "));// no transform so don't attach

	ProjectileMovement->InitialSpeed = MovementSpeed; // see UProjectileMovementComponent variables
	ProjectileMovement->MaxSpeed = MovementSpeed; // contstant projectile movement

	InitialLifeSpan = 3.0f;// AActor set lifespan variable
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

