// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemClassBase.generated.h"

UCLASS()
class TRAININGCAMP_API AItemClassBase : public AActor
{
	GENERATED_BODY()
	
	/** Capsula de colisión para interacciones */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class UCapsuleComponent* CollisionCapsule;
	

public:	
	// Sets default values for this actor's properties
	AItemClassBase();

	/** Mesh principal del ítem */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* ItemMesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Mapa para detallar los efectos de los ítems junto a su valor */
	UPROPERTY(EditAnywhere)
	TMap<FName, float> ItemList;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Control de colisiones
	void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
