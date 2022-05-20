// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

class ATankPawn;

/**
 * 
 */
UCLASS()
class TANK_ISOBKO_API ATankController : public APlayerController
{
	GENERATED_BODY()


protected:
	UPROPERTY()
		ATankPawn* TankPawn;

public:
	ATankController();
	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	
};