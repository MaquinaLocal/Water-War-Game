// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/LanternBase.h"
#include "Components/RectLightComponent.h"
#include "GameFramework/Actor.h"

//////////////////////////////////////////////////////////////////////
// Sets default values for this component's properties
ULanternBase::ULanternBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//Creación del scene component y anclaje como el root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Creación de la luz puntual y anclaje al componente de escena
	RectLight = CreateDefaultSubobject<URectLightComponent>(TEXT("SpotLight"));
	RectLight->SetupAttachment(RootComponent);

	//Valores por defecto
	RectLight->Intensity = 2000.0f;
	RectLight->LightColor = FColor::White;

	//Inicialización del estado de la luz
	bIsLightOn = true;

}


// Called when the game starts
void ULanternBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULanternBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


//////////////////////////////////////////////////////////////////////
//Función que cambia el estado de la luz: prendido / apagado
void ULanternBase::ToggleLight()
{
	if (RectLight)
	{
		bIsLightOn = !bIsLightOn;
		RectLight->SetVisibility(bIsLightOn);
	}
}
