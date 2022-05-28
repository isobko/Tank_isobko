// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

class UArrowComponent;

UCLASS()
class TANK_ISOBKO_API ACannon : public AActor
{
	GENERATED_BODY()
protected:
	virtual  void BeginPlay() override;
	void Reload();
	// Модель пушки
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* CannonMesh;
	// Точка из которой будет стрельба
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* ProjectileSpawnPoint;
	// Скорострельность
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Params")
	float FireRate = 1.0f;
	// Дальность стрельбы
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Params")
	float FireRange = 1000.0f;
	// Урон
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Params")
	float FireDamage = 1.0f;
	// Тип пушки
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Params")
	ECannonType CannonType = ECannonType::FireProjectile;
	// Количество снарядов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Params")
	int Ammo = 5;
	// Структура, использующаяся для работы с таймерами.
	FTimerHandle ReloadTimer;
	// Готовность пушки к стрельбе
	bool bReadyToFire = false;
	// Включение безконечного боезопаса
	bool bInfinityAmmo = false;

public:	
	ACannon();
	//Fire
	void FireLeft();
	void FireRight();
	void DebugLine(FColor Color);
	bool IsReadyToFire();
	// Ammo
	void LogAmmoCount();
	bool InfinityAmmo();
};
