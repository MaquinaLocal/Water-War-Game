// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PistolCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Character/ProjectileBase.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Damageable.h"
#include "AffectPlayer.h"

#define COLLISION_WEAPON		ECC_GameTraceChannel1
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

	AimingHelper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Aim"));
	AimingHelper->SetupAttachment(GetRootComponent());


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

	UpdateReticleByRayTrace();

}


void APistolCharacter::UpdateReticleByRayTrace()
{
	FVector LineStart = PistolMesh->GetComponentLocation();
	FVector Rotation = PistolMesh->GetForwardVector();
	FVector LineEnd = LineStart + -Rotation * TraceRange;

	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECC_Visibility))
	{
		AimingHelper->SetWorldLocation(HitResult.ImpactPoint);

		FRotator SurfaceRotation = HitResult.ImpactNormal.Rotation();
		AimingHelper->SetWorldRotation(SurfaceRotation);
	}
}


// Called to bind functionality to input
void APistolCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("LookUp", this, &APistolCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &APistolCharacter::TurnRight);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APistolCharacter::PistolShoot);
	PlayerInputComponent->BindAction("ToggleAmmo", IE_Pressed, this, &APistolCharacter::ToggleAmmo);
}


void APistolCharacter::LookUp(float Val)
{
	if (Val != 0.0f)
	{
		FRotator NewRotation(Val, 0.0f, 0.0f);
		PistolMesh->AddRelativeRotation(NewRotation);
		FireLocation->AddRelativeRotation(NewRotation*-1);
	}
}


void APistolCharacter::TurnRight(float Val)
{
	if (Val != 0.0f)
	{
		FRotator NewRotation(0.0f, Val, 0.0f);
		PistolMesh->AddRelativeRotation(NewRotation);
		FireLocation->AddRelativeRotation(NewRotation);
	}
}


void APistolCharacter::ToggleAmmo()
{
	if (CurrentAmmo == 1)
		CurrentAmmo = 2;
	else
		CurrentAmmo = 1;
}


void APistolCharacter::PistolShoot()
{
	float PowerShot = 25.0f;
	float RegularShot = 10.0f;
	
	if (CurrentAmmo == 1 && GunWaterLevel >= RegularShot && bCanShoot == true)
	{
		RayTraceCast();
		
		GunWaterLevel -= RegularShot;
		CheckWaterLevel();

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundToPlay, GetActorLocation());
	}
	else if (GunWaterLevel <= 0.0f)
	{
		RayTraceCast();
		TakeDamage(1.0f);
	}
}


void APistolCharacter::CheckWaterLevel()
{
	if (GunWaterLevel <= 0.0f)
		bCanShoot = false;
	else
		bCanShoot = true;
}


void APistolCharacter::RechargeWaterLevel()
{
	GunWaterLevel = MaxWaterLevel;
	bCanShoot = true;
}


void APistolCharacter::RayTraceCast()
{
	//Castea el rayo que afecta a los enemigos
	FHitResult Hit = ShootingTrace();

	SpawnEmitterAtLocation(Hit.Location, FRotator::ZeroRotator);

	IDamageable* DamageInterface = Cast<IDamageable>(Hit.Actor);
	if (DamageInterface && BoneDamage.Contains(Hit.BoneName))
	{
		float DamageValue = BoneDamage[Hit.BoneName];
		DamageInterface->TakeDamage(WeaponDamage * DamageValue);
	}
	else if (DamageInterface)
	{
		DamageInterface->TakeDamage(WeaponDamage);
	}

	IAffectPlayer* WaterInterface = Cast<IAffectPlayer>(Hit.Actor);
	if (WaterInterface)
	{
		WaterInterface->GetPlayer(this);
	}
}


FHitResult APistolCharacter::ShootingTrace() const
{
	FHitResult HitInfo;
	FVector LineStart = FireLocation->GetComponentLocation();
	FVector Forward = FireLocation->GetForwardVector();
	FVector LineEnd = LineStart + Forward * TraceRange;

	GetWorld()->LineTraceSingleByChannel(HitInfo, LineStart, LineEnd, COLLISION_WEAPON);

	DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Cyan, false, 0.2f, 0, 1);

	return HitInfo;
}

void APistolCharacter::TakeDamage(float Dmg)
{
	PlayerPoints -= Dmg;
}

void APistolCharacter::SpawnEmitterAtLocation(const FVector& Location, const FRotator& Rotation)
{
}

