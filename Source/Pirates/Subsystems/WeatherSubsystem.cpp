// Made by Jan Puto 2023 :>


#include "Pirates/Subsystems/WeatherSubsystem.h"

void UWeatherSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("WeathreSubsystem Initialized."));
	GetWorld()->OnWorldBeginPlay.AddUObject(this, UWeatherSubsystem::WorldBeginPlay);
}

void UWeatherSubsystem::WorldBeginPlay()
{
	FTimerDelegate TryChangeWindDirectionDelegate;
	TryChangeWindDirectionDelegate.BindUObject(this, UWeatherSubsystem::TryChangeWindDirection);
	GetWorld()->GetTimerManager().SetTimer(TryChangeWindDirectionTimer, TryChangeWindDirectionDelegate, TryChangeWindDirectionInterval, true);
}

void UWeatherSubsystem::TryChangeWindDirection()
{
	DesiredWindRotation = FMath::RandRange(0, 360);

	FTimerDelegate TryChangeWindDirectionDelegate;
	TryChangeWindDirectionDelegate.BindUObject(this, UWeatherSubsystem::TryChangeWindDirection);
	GetWorld()->GetTimerManager().SetTimer(AddWindRotationTimer, AddWindRotationInterval, true;

	WorldWindDirection
}

void UWeatherSubsystem::AddWindDirection()
{

}
