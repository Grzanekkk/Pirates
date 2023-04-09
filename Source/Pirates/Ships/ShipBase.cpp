// Made by Jan Puto 2023 :>


#include "Pirates/Ships/ShipBase.h"
#include "Components/ArrowComponent.h"

// Sets default values
AShipBase::AShipBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MainMeshComponent");
	SetRootComponent(MainMeshComponent);

	WheelSpawnPosition = CreateDefaultSubobject<UArrowComponent>("WheelSpawnPosition");
	WheelSpawnPosition->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AShipBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

