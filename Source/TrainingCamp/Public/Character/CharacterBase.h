// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;

UCLASS()
class TRAININGCAMP_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

	/** Mesh para el Pawn principal (brazos) **/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FirstPersonMesh;

	/** Mesh para el arma principal **/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* WeaponMesh;

	/** Cámara primera persona **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	// Sets default values for this character's properties
	ACharacterBase();

	/** Cámara: Tasa de giro horizontal (en grados por segundo) **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Cámara: Tasa de giro vertical **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Movimiento lateral **/
	void MoveRight(float Val);

	/** Movimiento frontal **/
	void MoveForward(float Val);

	/** Camara: tasa de giro lateral **/
	void TurnAtRate(float Val);

	/** Camara: tasa de giro vertical **/
	void LookUpRate(float Val);

	/** Interfaz APawn para movimiento **/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
