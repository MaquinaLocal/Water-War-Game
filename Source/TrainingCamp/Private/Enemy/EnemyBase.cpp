// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

#define COLLISION		ECC_GameTraceChannel3
///////////////////////////////////////////////////////////////
// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(GetRootComponent());

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(CapsuleComponent);

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(SkeletalMesh, TEXT("RightHandWeapon"));

	// Vida inicial del enemigo
	EnemyHP = 1000.f;
}


// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetVelocity().Size() > 0)
	{
		isMoving = true;
		OrientRotationToMovement();
	}
	else
		isMoving = false;
}

void AEnemyBase::OrientRotationToMovement()
{
	FRotator NewRotation = GetVelocity().Rotation();

	SetActorRotation(NewRotation);
}

void AEnemyBase::ShootPlayer()
{
	FHitResult HitInfo;
	FVector LineStart = WeaponMesh->GetComponentLocation();
	FVector Forward = WeaponMesh->GetForwardVector();
	FVector LineEnd = LineStart + Forward * TraceRange;

	GetWorld()->LineTraceSingleByChannel(HitInfo, LineStart, LineEnd, COLLISION);
	DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Orange, false, 1.0f);

}

///////////////////////////////////////////////////////////////
// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Daño que recibe el personaje
void AEnemyBase::TakeDamage(float Dmg)
{
	UE_LOG(LogTemp, Warning, TEXT("Enter"));
	DamageTaken = Dmg;
	EnemyHP -= Dmg;
	//if (EnemyHP <= 0)
		//Destroy();

	// Implementación del timer, luego del tiempo establecido cambia el valor DamageTaken a cero
	GetWorld()->GetTimerManager().SetTimer(ChangeDmgValueTimer, this, &AEnemyBase::RestoreValue, TimerDelay, true);
}


void AEnemyBase::RestoreValue()
{
	DamageTaken = 0;
}