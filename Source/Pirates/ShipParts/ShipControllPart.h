// Made by Jan Puto 2023 :>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pirates/Interfaces/PirateInteractionInterface.h"
#include "ShipControllPart.generated.h"

UCLASS()
class PIRATES_API AShipControllPart : public AActor, public IPirateInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShipControllPart();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintNativeEvent)
	virtual void AddControllValue(float ControllDirection);

	UFUNCTION(BlueprintImplementableEvent)
	void AddControllValueBP(float ControllDirection);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Settings")
	float ControllMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Settings")
	float ControllMinBounds = -100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Settings")
	float ControllMaxBounds = 100.f;

};
