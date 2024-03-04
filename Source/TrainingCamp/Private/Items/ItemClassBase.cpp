// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemClassBase.h"
#include "Components/CapsuleComponent.h"
#include "Character/CharacterBase.h"


/////////////////////////////////////////////////////////////////////////////
// Sets default values
AItemClassBase::AItemClassBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Esfera de colisión
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	RootComponent = CollisionCapsule;

	//Defaults para la capsula
	CollisionCapsule->InitCapsuleSize(50.0f, 50.0f);

	//Skeletal Mesh
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);

}


// Called when the game starts or when spawned
void AItemClassBase::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AItemClassBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/////////////////////////////////////////////////////////////////////////////
// Casteo a Player
void AItemClassBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ACharacterBase* Player = Cast<ACharacterBase>(OtherActor);
	if (OtherActor)
	{
		if (ItemList.Contains("GetLife") && ItemList["GetLife"] > 0)
		{
			float UpdateLife = ItemList["GetLife"];
			float CurrentHP = Player->PlayerHP;
			Player->PlayerHP += (CurrentHP * UpdateLife);
		}

		if (ItemList.Contains("GetArmor") && ItemList["GetArmor"] > 0)
		{
			float UpdateArmor = ItemList["GetArmor"];
			float CurrentArmor = Player->PlayerArmor;
			Player->PlayerArmor += (CurrentArmor * UpdateArmor);
		}
	}
}