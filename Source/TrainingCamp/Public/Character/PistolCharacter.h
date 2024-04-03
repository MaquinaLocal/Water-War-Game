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

	//Componente Camara
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* PistolCameraComponent;

	//Mesh para pistola
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* PistolMesh;

	//Punto donde sale el disparo
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	USceneComponent* FireLocation;

	//Retícula de arma
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* AimingHelper;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Cambiar posición de la retícula
	void UpdateReticleByRayTrace();

	//Seleccionar el actor para spawnear
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AActor> BPtoSpawn;

	//Agregar impulso
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Impulse Force")
	float ImpulseForce = 500.0f;

	//Mapa de daño por huesos
	UPROPERTY(EditAnywhere, Category = "Damage Stats")
	TMap<FName, float> BoneDamage;

	//Daño del arma
	UPROPERTY(EditAnywhere, Category = "Damage Stats")
	float WeaponDamage = 1.0f;

	//Nivel de agua actual y Nivel de agua total del arma
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float GunWaterLevel = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Stats")
	float MaxWaterLevel = 100.0f;

	//Puntos de jugador (similar a vida)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Win Condition")
	float PlayerPoints = 20.0f;

	//Sonido de disparo arma
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* FireSound;

	//Sonido agua agotada
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* NoAmmoSound;

	//Sonido recarga de agua
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* ReloadAmmoSound;

	//Sonido daño recibido
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* TakeDamageSound;

	
	//Casteo del rayo para disparo
	void RayTraceCast();
	FHitResult ShootingTrace() const;
	float TraceRange = 5000.0f;

	bool bCanShoot = true;
	int8 CurrentAmmo = 1;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movimiento vertical y horizontal
	void LookUp(float Val);
	void TurnRight(float Val);

	//disparo del arma
	void PistolShoot();

	//cambiar tipo de munición
	void ToggleAmmo();

	//Recargar nivel de agua
	void RechargeWaterLevel();

	//Chequear nivel actual de agua
	void CheckWaterLevel();

	//Recibir daño del enemigo
	void PlayerReceiveDamage(float Dmg);

	//Emisión de partículas
	void SpawnEmitterAtLocation(const FVector& Location, const FRotator& Rotation);

	//Reproducir sonido
	void PlaySoundAtLocation(USoundBase* SoundToPlay);

};
