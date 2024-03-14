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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AActor> BPtoSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Impulse Force")
	float ImpulseForce = 100.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LookUp(float Val);
	void TurnRight(float Val);
	void CannonBall();
};
