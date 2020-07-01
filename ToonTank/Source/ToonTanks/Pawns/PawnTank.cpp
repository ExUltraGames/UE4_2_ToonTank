// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "Camera/CameraComponent.h" // forward deckares
#include "GameFramework/SpringArmComponent.h"

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Rotate();// works best this way around with rotate first then move
	Move();

	if (PlayerControllerRef)
	{
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult); // OUT hitresult of cursor
		FVector HitLocation = TraceHitResult.ImpactPoint; // place in world trace has hit // see variables . impactpoint

		RotateTurret(HitLocation); // from parent class // already accounted for vertical in parent function
	}

}

// Called to bind functionality to input // instead of calling UInputComponent and using UNavMovementComponent
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);// bind inputs
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	//call fire function
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);//no () on function
}

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0); // only affect X
}

void APawnTank::CalculateRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0); // only affect Yaw
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true); // true = a sweepcheck = collision on
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();

	//Hide player on death create new function for this

	// remove Destroy();as fro demo only to show poor handling
}