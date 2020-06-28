// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Kismet/GameplayStatics.h"//for apply damage function


// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; 

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh; 

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement "));// no transform so don't attach

	ProjectileMovement->InitialSpeed = MovementSpeed; 
	ProjectileMovement->MaxSpeed = MovementSpeed; 

	InitialLifeSpan = 3.0f;
}


// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();// get ref to owning actor

	if (!MyOwner) { return; }

	//checks avialable due to SETOWNER() in pawnbase
	//If the OtherActors isn't self or owner && exists, the apply damage
	if (OtherActor != NULL && OtherActor != this && OtherActor != MyOwner)// prevents damaging pawn that spawned and protects
	{
		//std unreal function applydamage from Gameplaystatics
		UGameplayStatics::ApplyDamage(
			OtherActor, 
			Damage, 
			MyOwner->GetInstigatorController(), 
			this, 
			DamageType);
	}
	//Do a bunch of effects here during polish phase
	
	Destroy();
}
