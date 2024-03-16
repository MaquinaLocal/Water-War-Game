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

	UPROPERTY(EditAnywhere)
	TArray<AActor*> WayPoints;

	UPROPERTY(BlueprintReadOnly)
	bool isMoving;

protected:
	//Creación del timer para el sistema de estadísticas
	FTimerHandle ChangeDmgValueTimer;
	float TimerDelay = 0.2f;
	void RestoreValue();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TakeDamage(float Dmg) override;

	void OrientRotationToMovement();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
