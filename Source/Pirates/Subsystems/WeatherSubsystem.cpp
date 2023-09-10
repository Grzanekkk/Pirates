// Made by Jan Puto 2023 :>


#include "Pirates/Subsystems/WeatherSubsystem.h"

void UWeatherSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("WeathreSubsystem Initialized."));
}