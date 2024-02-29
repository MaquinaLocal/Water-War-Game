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

	/** Mesh para el Pawn principal (brazos) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FirstPersonMesh;

	/** Mesh para el arma principal */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* WeaponMesh;

	/** C�mara primera persona */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Componente de escena para la posici�n del line trace */
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	USceneComponent* FireLocation;
	
public:
	// Sets default values for this character's properties
	ACharacterBase();

	/** C�mara: Tasa de giro horizontal (en grados por segundo) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** C�mara: Tasa de giro vertical */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Distancia de dibujado del rayo */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	float WeaponRange;

	/** Da�o de arma del player */
	UPROPERTY(EditAnywhere, Category = "Weapon")
	float WeaponDamage;

	/** Mapa de da�o por zonas, editable desde BP */
	UPROPERTY(EditAnywhere)
	TMap<FName, float> BoneDamage;

protected:
	
	/** Movimiento lateral */
	void MoveRight(float Val);

	/** Movimiento frontal */
	void MoveForward(float Val);

	/** Disparo de arma principal */
	void Shoot();

	/** Struct para el disparo del rayo */
	FHitResult WeaponTrace() const;

	/** Interfaz APawn para movimiento */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
