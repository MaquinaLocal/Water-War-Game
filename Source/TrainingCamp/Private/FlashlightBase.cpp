// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashlightBase.h"
#include "Components/RectLightComponent.h"

////////////////////////////////////////////////////////////////
// Sets default values
AFlashlightBase::AFlashlightBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Mesh de la linterna
	LightMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LightMesh"));
	LightMesh->SetupAttachment(GetRootComponent());

	//Iluminación rectangular
	RectLight = CreateDefaultSubobject<URectLightComponent>(TEXT("RectLight"));
	RectLight->SetupAttachment(LightMesh);

	//Defaults values para la luz
	RectLight->Intensity = 5000.0f;
	RectLight->LightColor = FColor::White;

	bIsLightOn = true;

}

// Called when the game starts or when spawned
void AFlashlightBase::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AFlashlightBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////
// Funciones
void AFlashlightBase::ToggleFlashlight()
{
	bIsLightOn = !bIsLightOn;
	RectLight->SetVisibility(bIsLightOn);
}