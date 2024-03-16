// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AIControllerBase.h"
#include "Enemy/EnemyBase.h"
#include "TimerManager.h"


AAIControllerBase::AAIControllerBase()
{
	Radius = 500;
	TimerDelay = 2.0f;
}


void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	MoveControlledPawnToLocation();

	GetWorld()->GetTimerManager().SetTimer(WayPointTimer, this, &AAIControllerBase::MoveToNextWayPoint, TimerDelay, true);
}


void AAIControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AAIControllerBase::MoveControlledPawnToLocation()
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(GetPawn());
	if (Enemy)
	{
		FVector TargetPoint = Enemy->WayPoints[CurrentWayPoint]->GetActorLocation();
		MoveToLocation(TargetPoint);
	}
}


void AAIControllerBase::MoveToNextWayPoint()
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(GetPawn());

	if (Enemy) {
		FVector EnemyPosition = Enemy->GetActorLocation();
		FVector TargetPoint = Enemy->WayPoints[CurrentWayPoint]->GetActorLocation();
	
		float Dist = FVector::Dist(EnemyPosition, TargetPoint);

		UE_LOG(LogTemp, Warning, TEXT("Distante: %f"), Dist);

		if (Dist < 150.0f)
		{
			CurrentWayPoint++;

			if (CurrentWayPoint >= Enemy->WayPoints.Num())
				CurrentWayPoint = 0;

			FVector NewTargetPoint = Enemy->WayPoints[CurrentWayPoint]->GetActorLocation();
			MoveToLocation(NewTargetPoint);
		}
	}
}

