// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/FriendlyTarget.h"
#include "Character/PistolCharacter.h"
#include "AffectPlayer.h"
#include "TimerManager.h"

// Sets default values
AFriendlyTarget::AFriendlyTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFriendlyTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFriendlyTarget::GetPlayer(AActor* Player)
{
	APistolCharacter* PlayerRef = Cast<APistolCharacter>(Player);
	if (PlayerRef)
	{
		float Dmg = 1.0f;
		PlayerRef->TakeDamage(Dmg);
	}

	bGetHit = true;

	GetWorld()->GetTimerManager().SetTimer(AnimTimer, this, &AFriendlyTarget::ChangeHitValue, Delay, false);

}

void AFriendlyTarget::ChangeHitValue()
{
	bGetHit = false;
}

// Called every frame
void AFriendlyTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bGetHit == false)
	{
		FVector Movement = FVector(WalkSpeed * DeltaTime, 0, 0);
		AddActorLocalOffset(Movement);
	}
}

