// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "CharacterBase.generated.h"


UCLASS()
class TRAININGCAMP_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
	
	/** Cámara primera persona */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Componente de escena para la posición del line trace */
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	USceneComponent* FireLocation;
	
public:
	// Sets default values for this character's properties
	ACharacterBase();

	/** Cámara: Tasa de giro horizontal (en grados por segundo) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Cámara: Tasa de giro vertical */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Distancia de dibujado del rayo */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	float WeaponRange;

	/** Daño de arma del player */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	float WeaponDamage;

	/** Mapa de daño por zonas, editable desde BP */
	UPROPERTY(EditAnywhere)
	TMap<FName, float> BoneDamage;

	/** Vida de Jugador */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
	float PlayerHP;

	/** Armadura de Jugador */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
	float PlayerArmor;

	/** Velocidad del jugador */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
	float PlayerSpeed;

	/** Actualizar la velocidad de movimiento */
	void ChangeMovementSpeed(float Value);

protected:
	
	/** Movimiento lateral */
	//void MoveRight(float Val);

	/** Movimiento frontal */
	//void MoveForward(float Val);

	/** Disparo de arma principal */
	void Shoot();

	/** Struct para el disparo del rayo */
	FHitResult WeaponTrace() const;

	/** Interfaz APawn para movimiento */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
