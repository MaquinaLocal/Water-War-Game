// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "PistolCharacter.generated.h"

UCLASS()
class TRAININGCAMP_API APistolCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APistolCharacter();

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* PistolCameraComponent;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* PistolMesh;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	USceneComponent* FireLocation;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* AimingHelper;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateReticleByRayTrace();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AActor> BPtoSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Impulse Force")
	float ImpulseForce = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Damage Stats")
	TMap<FName, float> BoneDamage;

	UPROPERTY(EditAnywhere, Category = "Damage Stats")
	float WeaponDamage = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float GunWaterLevel = 100.0f;
	bool bCanShoot = true;
	void CheckWaterLevel();
	void RechargeWaterLevel();

	int8 CurrentAmmo = 1;

	FHitResult ShootingTrace() const;
	float TraceRange = 5000.0f;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LookUp(float Val);
	void TurnRight(float Val);
	void PistolShoot();
	void ToggleAmmo();
};
