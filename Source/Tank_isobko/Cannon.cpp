
#include "Cannon.h"

#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Engine/RendererSettings.h"


ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = sceneCpm;
	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(RootComponent);
	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::FireLeft()
{
	if(!IsReadyToFire())
	{
		return;
	}
	bReadyToFire = false;
	// Проверка что есть снаряды, если нет, то стрельба невозможна
	if (Ammo <= 0)
	{
		return;
	}
	Ammo = Ammo - 1;
	
	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 2, FColor::Green, "Fire - Projectile");
		DebugLine(FColor::Green);
		//LogAmmoCount();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 2, FColor::Red, "Fire - Trace");
		DebugLine(FColor::Red);
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
	
}

void ACannon::FireRight()
{
	if(!IsReadyToFire())
	{
		return;
	}
	GEngine->AddOnScreenDebugMessage(10, 2, FColor::Blue, "Fire - Special");
	DebugLine(FColor::Blue);
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}

bool ACannon::InfinityAmmo()
{
	return bInfinityAmmo;
}

void ACannon::Reload()
{
	bReadyToFire = true;
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
}

void ACannon::DebugLine(FColor Color)
{
	FVector StartVector = ProjectileSpawnPoint->GetComponentLocation();
	FVector EndVector = StartVector + (ProjectileSpawnPoint->GetForwardVector() * FireRange);
	DrawDebugLine(GetWorld(), StartVector, EndVector, Color, false, 0.2f, 0, 5);
}

//void ACannon::LogAmmoCount()
//{
//	GEngine->AddOnScreenDebugMessage(10, 2, FColor::Blue, "Fire - Special" + FString::FromInt(Ammo));
//	//FString AmmoInfo = "Ammo : " + Ammo;
//}
