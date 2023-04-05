// Made by Jan Puto 2023 :>

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterEnums.generated.h"

UENUM(BlueprintType)
enum class EPirateCharacterState : uint8
{
	NONE UMETA(DisplayName = "None"),
	WALK UMETA(DisplayName = "Walk"),
	STEERING_WHEEL UMETA(DisplayName = "Steering Wheel"),
	RAISING_SAILS UMETA(DisplayName = "Raising Sails"),
	ADJUSTING_SAILS UMETA(DisplayName = "Adjusting Sails"),
	MAX
};

/**
 * 
 */
UCLASS()
class PIRATES_API UCharacterEnums : public UObject
{
	GENERATED_BODY()
	
};
