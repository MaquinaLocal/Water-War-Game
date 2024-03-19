// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SceneTargetBase.h"
#include "TimerManager.h"
#include "AffectPlayer.h"

// Sets default values
ASceneTargetBase::ASceneTargetBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASceneTargetBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(DestroyDelayHandle, this, &ASceneTargetBase::DestroySelf, Delay, false);
	
}

void ASceneTargetBase::GetPlayer(AActor* Player)
{
	FRotator NewRotation = FRotator(90.0f, 0.0f, 0.0f);
	AddActorLocalRotation(NewRotation);
}

void ASceneTargetBase::DestroySelf()
{
	Destroy();
}

// Called every frame
void ASceneTargetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(FVector(0.0f, Speed, 0.0f) * DeltaTime);
}

