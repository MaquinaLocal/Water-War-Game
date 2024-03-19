// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AffectPlayer.h"
#include "GameFramework/Actor.h"
#include "SceneTargetBase.generated.h"

UCLASS()
class TRAININGCAMP_API ASceneTargetBase : public AActor, public IAffectPlayer
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneTargetBase();

	UPROPERTY(EditAnywhere, Category = "MovSpeed")
	float Speed = 100.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetPlayer(AActor* Player) override;

	UPROPERTY(EditAnywhere, Category = "SpawnTime")
	float Delay = 5.0f;
	FTimerHandle DestroyDelayHandle;
	void DestroySelf();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
