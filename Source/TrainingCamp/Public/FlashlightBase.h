// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlashlightBase.generated.h"

UCLASS()
class TRAININGCAMP_API AFlashlightBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USkeletalMeshComponent* LightMesh;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class URectLightComponent* RectLight;
	
public:	
	// Sets default values for this actor's properties
	AFlashlightBase();
	
	//Cambia el estado de la luz, llamado desde un Character
	UFUNCTION(BlueprintCallable, Category = "FlashLight")
	void ToggleFlashlight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Estado de la luz
	bool bIsLightOn;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
