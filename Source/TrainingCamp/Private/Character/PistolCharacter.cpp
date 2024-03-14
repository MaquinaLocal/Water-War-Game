// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PistolCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Character/ProjectileBase.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
APistolCharacter::APistolCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	PistolCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PistolCamera"));
	PistolCameraComponent->SetRelativeLocation(FVector(0, 0, 64.f));
	PistolCameraComponent->SetupAttachment(GetCapsuleComponent());

	PistolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PistolMesh"));
	PistolMesh->SetupAttachment(PistolCameraComponent);

	FireLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FireLocation"));
	FireLocation->SetupAttachment(PistolCameraComponent);



}

// Called when the game starts or when spawned
void APistolCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APistolCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APistolCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("LookUp", this, &APistolCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &APistolCharacter::TurnRight);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APistolCharacter::CannonBall);
}

void APistolCharacter::LookUp(float Val)
{
	if (Val != 0.0f)
	{
		Val = -Val;
		FRotator NewRotation(0.0f, 0.0f, Val);
		PistolMesh->AddRelativeRotation(NewRotation);
	}
}

void APistolCharacter::TurnRight(float Val)
{
	if (Val != 0.0f)
	{
		FRotator NewRotation(0.0f, Val, 0.0f);
		PistolMesh->AddRelativeRotation(NewRotation);
	}
}

void APistolCharacter::CannonBall()
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(BPtoSpawn.Get(), GetActorLocation(), GetActorRotation());
	if (SpawnedActor)
	{
		UPrimitiveComponent* SpawnedRoot = Cast<UPrimitiveComponent>(SpawnedActor->GetRootComponent());
		if (SpawnedRoot)
		{
			FVector Impulse = FVector(0.0f, 0.0f, 0.0f);
			SpawnedRoot->AddImpulse(Impulse, NAME_None, true);
		}
	}
}

