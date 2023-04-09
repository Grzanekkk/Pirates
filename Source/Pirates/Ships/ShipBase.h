// Made by Jan Puto 2023 :>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipBase.generated.h"

class UArrowComponent;

UCLASS()
class PIRATES_API AShipBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AShipBase();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

#pragma region Components

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Components")
	TObjectPtr<UStaticMeshComponent> MainMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Components")
	TObjectPtr<UArrowComponent> WheelSpawnPosition;

#pragma endregion
};
