// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Damageable.h"
#include "Items/LanternBase.h"

#define COLLISION_WEAPON		ECC_GameTraceChannel1

/////////////////////////////////////////////////////////////
// Sets default values

ACharacterBase::ACharacterBase()
{
	/** Creación de cápsula */
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	/** Creación de Componente Cámara **/
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera)"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0, 0, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	/** Creación de Mesh de Jugador */
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	/** Creación de Mesh de Arma */
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->bCastDynamicShadow = false;
	WeaponMesh->CastShadow = false;
	WeaponMesh->SetupAttachment(FirstPersonMesh, TEXT("GripPoint"));

	/** Creación del componente de escena */
	FireLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FireLocation"));
	FireLocation->SetupAttachment(FirstPersonMesh, TEXT("GripPoint"));

	WeaponRange = 3000.0f;
	WeaponDamage = 500.0f;
}

/////////////////////////////////////////////////////////////
// Input

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Salto
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Disparo
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACharacterBase::Shoot);

	// Movimientos de personaje
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);

	// Rotación de cámara
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Uso de linterna
	PlayerInputComponent->BindAction("Lantern", IE_Pressed, this, &ACharacterBase::ToggleLight);
}

void ACharacterBase::Shoot()
{
	FHitResult HitInfo = WeaponTrace();

	// Casteo a la interfaz de daño para enemigos y daño según zona de cuerpo
	IDamageable* DamageInterface = Cast<IDamageable>(HitInfo.Actor);
	if (DamageInterface && BoneDamage.Contains(HitInfo.BoneName))
	{
		float DamageValue = BoneDamage[HitInfo.BoneName];
		DamageInterface->TakeDamage(WeaponDamage * DamageValue);	
	}
}

void ACharacterBase::ToggleLight()
{
	UE_LOG(LogTemp, Warning, TEXT("Enter"));

	ULanternBase* LightComponent = this->FindComponentByClass<ULanternBase>();
	
	if (LightComponent)
		LightComponent->ToggleLight();
	else
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
}

// Struct que se encarga de generar el rayo del arma
FHitResult ACharacterBase::WeaponTrace() const
{
	// Variable que guarda la información del rayo
	FHitResult ImpactInfo;
	// Posición de inicio
	FVector LineOrigin = FireLocation->GetComponentLocation();
	// Posición final (con rotación)
	FRotator CamRot = FireLocation->GetComponentRotation();
	FVector LineEnd = LineOrigin + CamRot.Vector() * WeaponRange;
	// Creación del rayo
	GetWorld()->LineTraceSingleByChannel(ImpactInfo, LineOrigin, LineEnd, COLLISION_WEAPON);

	//Dibujado de linea desde inicio hasta final del rayo
	DrawDebugLine(GetWorld(), LineOrigin, LineEnd, FColor::Green, false, 3);

	return ImpactInfo;
}

void ACharacterBase::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		// Add movement in that direction
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void ACharacterBase::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		// Add movement in that direction
		AddMovementInput(GetActorForwardVector(), Val);
	}
}


