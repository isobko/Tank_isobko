// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Cannon.h"
#include "TankController.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	RootComponent = BodyMesh;
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
	TurretMesh->SetupAttachment(BodyMesh);
	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController = Cast<ATankController>(GetController());
	SetupCannon();
}

void ATankPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Tank movement
	FVector CurrentLocationTank = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector MovePosition = CurrentLocationTank + ForwardVector * MoveSpeed * TargetForwardAxisValue * DeltaSeconds;
	SetActorLocation(MovePosition, true);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Position Pawn : %s"), *MovePosition.ToString()));
	
	// Tank rotation
	CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue, TargetRightAxisValue, RotateInterpolationKey);
	float YawRotation = RotationSpeed * CurrentRightAxisValue * DeltaSeconds;
	FRotator CurrentRotationTank = GetActorRotation();
	YawRotation = CurrentRotationTank.Yaw + YawRotation;
	FRotator NewRotation = FRotator(0, YawRotation, 0);
	SetActorRotation(NewRotation);
	//UE_LOG(LogTemp, Warning, TEXT("CurrentRightAxisValue : %f, TargetRightAxisValue: %f"), CurrentRightAxisValue, TargetRightAxisValue);

	// Turret rotation
	if (TankController)
	{
		FVector MousePosition = TankController->GetMousePosition();
		//UE_LOG(LogTemp, Warning, TEXT("Rotation: %s"), *MousePosition.ToString());
		RotateTurretTo(MousePosition);
	}
}

void ATankPawn::RotateTurretTo(FVector TargetPosition)
{
	FRotator TargetRotationTurret = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	FRotator CurrentRotationTurret = TurretMesh->GetComponentRotation();
	TargetRotationTurret.Pitch = CurrentRotationTurret.Pitch;
	TargetRotationTurret.Roll = CurrentRotationTurret.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(CurrentRotationTurret, TargetRotationTurret, TurretRotateInterpolationKey));
	// DEBUG
	//UE_LOG(LogTemp, Warning, TEXT("Rotation: %s"), *TargetRotation.ToString());
}

void ATankPawn::MoveForward(float Value)
{
	TargetForwardAxisValue = Value;
}

void ATankPawn::RotateRight(float Value)
{
	TargetRightAxisValue = Value;
}

void ATankPawn::FireLeft()
{
	if(Cannon)
	{
		Cannon->FireLeft();
	}
}

void ATankPawn::FireRight()
{
	if(Cannon)
	{
		Cannon->FireRight();
	}
}

void ATankPawn::SetupCannon()
{
	if(Cannon)
	{
		Cannon->Destroy();
	}
	FActorSpawnParameters spawnParams;
	spawnParams.Instigator = this;
	spawnParams.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, spawnParams);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}