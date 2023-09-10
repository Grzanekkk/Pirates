// Made by Jan Puto 2023 :>

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WeatherSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PIRATES_API UWeatherSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY()
	float TryChangeWindDirectionInterval = 5.f;

	UPROPERTY()
	float AddWindRotationInterval = 0.2f;

	UPROPERTY()
	float AddWindRotationRate = 0.1f;

protected:
	UFUNCTION()
	void WorldBeginPlay();

	UFUNCTION()
	void TryChangeWindDirection();

	UFUNCTION()
	void AddWindDirection();

	UPROPERTY()
	float WorldWindDirection = 0;

	UPROPERTY()
	float DesiredWindRotation = 0;

	UPROPERTY()
	FTimerHandle TryChangeWindDirectionTimer;

	UPROPERTY()
	FTimerHandle AddWindRotationTimer;

};
