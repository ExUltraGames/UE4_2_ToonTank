// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h" // for ref to gamemode
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // reactive class to function calls, no tick

	Health = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	Owner = GetOwner();
	if(Owner) 
	{
		// bind owner to damaage function
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage); // same as OnHit
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Health Component has no reference to Owner"));
	}
	
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* EventInstigator, AActor* DamageCauser)
{
	if (Damage == 0 || Health == 0) // check for error || if already dead
	{
		return;
	}
	
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth); // could use absolute maxhealth instead of defaultHeakth if wanted

	if (Health <= 0) // updated Helath value, check of alive
	{
		if (GameModeRef) // check if valid reference
		{
			GameModeRef->ActorDied(Owner); // call Actordied func in GameMode and pass in the ref to owner
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health has No Game Mode ref!")); 
			// use GameMode to deal with death // if more props may want to do differently // same logic but instead pass to owning actor and deal there  
		}
	}
}


