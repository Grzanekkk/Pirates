// Made by Jan Puto 2023 :>


#include "Pirates/ShipParts/ShipControllPart.h"

// Sets default values
AShipControllPart::AShipControllPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShipControllPart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShipControllPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShipControllPart::AddControllValue(float ControllDirection)
{
	AddControllValueBP(ControllDirection);
}
