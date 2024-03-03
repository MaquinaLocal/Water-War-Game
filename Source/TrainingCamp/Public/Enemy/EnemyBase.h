// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "GameFramework/Pawn.h"
#include "EnemyBase.generated.h"

UCLASS()
class TRAININGCAMP_API AEnemyBase : public APawn, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();

	UPROPERTY(EditAnywhere, Category = "Stats")
	float EnemyHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DamageTaken;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TakeDamage(float Dmg) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
