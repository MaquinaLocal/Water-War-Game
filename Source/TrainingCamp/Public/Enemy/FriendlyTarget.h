// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AffectPlayer.h"
#include "FriendlyTarget.generated.h"

UCLASS()
class TRAININGCAMP_API AFriendlyTarget : public AActor, public IAffectPlayer
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFriendlyTarget();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	float WalkSpeed = 100.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetPlayer(AActor* Player) override;

	UPROPERTY(BlueprintReadOnly)
	bool bGetHit = false;

	FTimerHandle AnimTimer;
	float Delay = 4.0f;
	void ChangeHitValue();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
