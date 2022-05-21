#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"


UENUM(BlueprintType)
enum class ECannonType: uint8
{
	FireProjectile = 0 UMETA(DisplayName = "Projectile"),
	FireTrace = 1 UMETA(DisplayName = "Trace")
};

UCLASS()
class TANK_ISOBKO_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};
