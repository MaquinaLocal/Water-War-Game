// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "TimerManager.h"


///////////////////////////////////////////////////////////////
// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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