// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAININGCAMP_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

	AAIControllerBase();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	int Radius;

	void MoveControlledPawnToLocation();

	int CurrentWayPoint = 0;

	FTimerHandle WayPointTimer;
	float TimerDelay;
	void MoveToNextWayPoint();


public:
	virtual void Tick(float DeltaTime) override;
	
};
