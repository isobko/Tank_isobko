// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

class ATankPawn;


UCLASS()
class TANK_ISOBKO_API ATankController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankController();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	FVector GetMousePosition() { return MousePosition; };
	
protected:
	virtual void BeginPlay() override;
	UPROPERTY()
	ATankPawn* TankPawn;
	UPROPERTY()
	FVector MousePosition;
	void MoveForward(float Value);
	void RotateRight(float Value);
	void FireRight();
	void FireLeft();
};
