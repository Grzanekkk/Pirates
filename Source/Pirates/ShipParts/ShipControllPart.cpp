// Made by Jan Puto 2023 :>


#include "Pirates/ShipParts/ShipControllPart.h"
#include "Pirates/Characters/PirateCharacterBase.h"
#include "Pirates/Enums/CharacterEnums.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AShipControllPart::AShipControllPart()
{
	PrimaryActorTick.bCanEverTick = true;

	RootArrowComponent = CreateDefaultSubobject<UArrowComponent>("RootArrowComponent");
	SetRootComponent(RootArrowComponent);

	PlayerLocationPoint = CreateDefaultSubobject<UArrowComponent>("PlayerLocationPoint");
	PlayerLocationPoint->SetupAttachment(GetRootComponent());

	InteractionWidgetLocationPoint = CreateDefaultSubobject<UArrowComponent>("InteractionWidgetLocationPoint");
	InteractionWidgetLocationPoint->SetupAttachment(GetRootComponent());

	MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MainMeshComponent");
	MainMeshComponent->SetupAttachment(GetRootComponent());

	InteractionAreaBoxComponent = CreateDefaultSubobject<UBoxComponent>("InteractionAreaBoxComponent");
	InteractionAreaBoxComponent->SetupAttachment(GetRootComponent());

	ControllPartCamera = CreateDefaultSubobject<UCameraComponent>("ControllPartCamera");
	ControllPartCamera->SetupAttachment(GetRootComponent());
	ControllPartCamera->bAutoActivate = false;

	PirateCharacterStateWhenControlling = EPirateCharacterState::NONE;
}

void AShipControllPart::Look(const FInputActionValue& Value)
{
	// Input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	FRotator DeltaRotation;
	DeltaRotation.Pitch = -LookAxisVector.Y;
	DeltaRotation.Yaw = LookAxisVector.X;
	DeltaRotation.Roll = 0.0f;

	FRotator FutureRotation = ControllPartCamera->GetRelativeRotation() + DeltaRotation;
	if (FutureRotation.Pitch > MinRotation.Pitch &&
		FutureRotation.Yaw > MinRotation.Yaw &&
		FutureRotation.Pitch < MaxRotation.Pitch &&
		FutureRotation.Yaw < MaxRotation.Yaw
		)
	{
		ControllPartCamera->AddLocalRotation(DeltaRotation);
	}
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

	FRotator NewRotation = ControllPartCamera->GetComponentRotation();
	NewRotation.Roll = 0.0f;
	ControllPartCamera->SetWorldRotation(NewRotation);
}

void AShipControllPart::AddControllValue(float ControllDirection)
{
	AddControllValueBP(ControllDirection);
}

void AShipControllPart::OnCameraBlendInFinished()
{
	if (ControllingPirateCharacter)
	{
		ControllingPirateCharacter->SetActorLocation(PlayerLocationPoint->GetComponentLocation());
		TObjectPtr<AController> Controller = ControllingPirateCharacter->GetController();
		Controller->SetControlRotation(PlayerLocationPoint->GetComponentRotation());
	}
}

#pragma region InteractionInterface

void AShipControllPart::Interact_Implementation(APawn* InstigatorPawn)
{
	ControllingPirateCharacter = Cast<APirateCharacterBase>(InstigatorPawn);
	if (ControllingPirateCharacter)
	{
		ControllingPirateCharacter->SetPlayerState(PirateCharacterStateWhenControlling);
		bIsPlayerUsingControllPart = true;
		ControllPartCamera->Activate();

		TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(ControllingPirateCharacter->GetController());
		PlayerController->SetViewTargetWithBlend(this, CameraBlendInTime);

		FTimerDelegate CameraBlendInDelegate;
		CameraBlendInDelegate.BindUFunction(this, "OnCameraBlendInFinished");
		GetWorld()->GetTimerManager().SetTimer(CameraBlendInTimer, CameraBlendInDelegate, CameraBlendInTime, false);
	}
}

bool AShipControllPart::CanInteract_Implementation(APawn* InstigatorPawn)
{
	return InteractionAreaBoxComponent->IsOverlappingActor(InstigatorPawn) && !bIsPlayerUsingControllPart;
}

void AShipControllPart::UnInteract_Implementation(APawn* InstigatorPawn)
{
	TObjectPtr<APirateCharacterBase> InstigatorPirateCharacter = Cast<APirateCharacterBase>(InstigatorPawn);
	if (ControllingPirateCharacter == InstigatorPirateCharacter)
	{
		ControllingPirateCharacter->SetPlayerState(EPirateCharacterState::WALK);
		bIsPlayerUsingControllPart = false;

		TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(ControllingPirateCharacter->GetController());
		PlayerController->SetViewTargetWithBlend(ControllingPirateCharacter, CameraBlendOutTime);
	}
}

bool AShipControllPart::CanUnInteract_Implementation(APawn* InstigatorPawn)
{
	TObjectPtr<APirateCharacterBase> InstigatorPirateCharacter = Cast<APirateCharacterBase>(InstigatorPawn);
	return ControllingPirateCharacter == InstigatorPirateCharacter && bIsPlayerUsingControllPart;
}

bool AShipControllPart::IsEnabled_Implementation()
{
	return !bIsPlayerUsingControllPart;
}

bool AShipControllPart::CanShowInteractionWidget_Implementation(APawn* InstigatorPawn)
{
	return IPirateInteractionInterface::Execute_CanInteract(this, InstigatorPawn);
}

FVector AShipControllPart::GetInteractionWidgetLocation_Implementation()
{
	return InteractionWidgetLocationPoint->GetComponentLocation();
}

#pragma endregion 