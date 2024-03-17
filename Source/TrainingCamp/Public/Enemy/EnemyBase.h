// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "EnemyBase.generated.h"

UCLASS()
class TRAININGCAMP_API AEnemyBase : public APawn, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();

	UPROPERTY(VisibleDefaultsOnly)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float EnemyHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DamageTaken;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> WayPoints;

	UPROPERTY(BlueprintReadOnly)
	bool isMoving;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Win Condition")
	float EnemyPoints = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Win Condition")
	float WeaponDamage = 1.0f;


protected:
	//Creación del timer para el sistema de estadísticas
	FTimerHandle ChangeDmgValueTimer;
	float TimerDelay = 0.2f;
	void RestoreValue();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TakeDamage(float Dmg) override;

	void OrientRotationToMovement();

	UFUNCTION(BlueprintCallable)
	void ShootPlayer();

	float TraceRange = 5000.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
