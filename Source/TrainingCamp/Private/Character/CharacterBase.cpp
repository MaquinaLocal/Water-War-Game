// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Damageable.h"
#include "Components/SpotLightComponent.h"


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

	/** Luz puntual */
	FlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLight"));
	FlashLight->SetupAttachment(FirstPersonCameraComponent);

	//Valores por defecto arma
	WeaponRange = 3000.0f;
	WeaponDamage = 500.0f;

	//Valores por defecto flashlight
	FlashLight->SetRelativeLocation(FVector(70.0f,20.0f,140.0f));
	FlashLight->SetRelativeRotation(FRotator::ZeroRotator);
	FlashLight->Intensity = 5000.0f;
	FlashLight->LightColor = FColor::White;
	bIsLightOn = false;
	FlashLight->SetVisibility(bIsLightOn);
	iteration = 0;
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
	PlayerInputComponent->BindAction("Flashlight", IE_Pressed, this, &ACharacterBase::ToggleLight);
	PlayerInputComponent->BindAction("LightColor", IE_Pressed, this, &ACharacterBase::ChangeColorOfLight);
	PlayerInputComponent->BindAction("LightIntensity", IE_Pressed, this, &ACharacterBase::ChangeIntensityOfLight);
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

// Prende / Apaga linterna
void ACharacterBase::ToggleLight()
{
	bIsLightOn = !bIsLightOn;
	FlashLight->SetVisibility(bIsLightOn);
}

// Cambia color de la luz
void ACharacterBase::ChangeColorOfLight()
{
	if (bIsLightOn == true)
		FlashLight->SetLightColor(FColor::MakeRandomColor());
}

// Cambio de intensidad de luz
void ACharacterBase::ChangeIntensityOfLight()
{
	if (bIsLightOn == true)
		FlashLight->SetIntensity(GetIntensityValue());
}
// Struct que devuelve el valor de intensidad
float ACharacterBase::GetIntensityValue()
{
	if (iteration == 0)
	{
		float NewIntensity = FlashLight->Intensity * 2;
		iteration = 1;
		return NewIntensity;
	}
	else if (iteration == 1)
	{
		float NewIntensity = FlashLight->Intensity / 2;
		iteration = 0;
		return NewIntensity;
	}
	else
		return 0.0f;
}


