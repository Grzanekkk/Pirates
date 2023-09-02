// Made by Jan Puto 2023 :>


#include "PirateCharacterBase.h"
#include "Pirates/Enums/CharacterEnums.h"
#include "Pirates/Components/PirateInteractionComponent.h"
#include "Pirates/ShipParts/ShipControllPart.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APirateCharacterBase::APirateCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	InteractionComponent = CreateDefaultSubobject<UPirateInteractionComponent>("InteractionComponent");

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	PlayerCharacterState = EPirateCharacterState::WALK;
}

// Called when the game starts or when spawned
void APirateCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void APirateCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APirateCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	SetPlayerActionsBasedOnState();
}

void APirateCharacterBase::SetPlayerState(EPirateCharacterState NewPlayerCharacterState)
{
	if (PlayerCharacterState != NewPlayerCharacterState)
	{
		PlayerCharacterState = NewPlayerCharacterState;

		SetPlayerActionsBasedOnState();
	}
}

void APirateCharacterBase::SetPlayerActionsBasedOnState()
{
	if (ensure(EnhancedInputComponent))
	{
		EnhancedInputComponent->ClearActionBindings();
		EnhancedInputComponent->ClearAxisBindings();

		switch (PlayerCharacterState)
		{
			case EPirateCharacterState::WALK:
			{
				//Jumping
				EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
				EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

				//Moving
				EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APirateCharacterBase::Move);

				//Looking
				EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APirateCharacterBase::Look);

				//Interaction
				EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APirateCharacterBase::Interact);

				break;
			}
			case EPirateCharacterState::STEERING_WHEEL:
			{
				SetPlayerActionsForShipControlls();

				break;
			}
			case EPirateCharacterState::RAISING_SAILS:
			{
				SetPlayerActionsForShipControlls();

				break;
			}
		}
	}
}

void APirateCharacterBase::SetPlayerActionsForShipControlls()
{
	//Looking
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APirateCharacterBase::SemiLockedLook);

	EnhancedInputComponent->BindAction(TurnWheelAction, ETriggerEvent::Triggered, this, &APirateCharacterBase::AddShipControllPartValue);

	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APirateCharacterBase::Interact);

}

void APirateCharacterBase::LockCamera()
{
	TObjectPtr<APlayerCameraManager> CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (CameraManager)
	{
		CameraManager->ViewPitchMax = 90.f;
		CameraManager->ViewPitchMin = 90.f;
		CameraManager->ViewRollMax = 90.f;
		CameraManager->ViewRollMin = 90.f;
		CameraManager->ViewYawMax = 90.f;
		CameraManager->ViewYawMin = 90.f;
	}
}

void APirateCharacterBase::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APirateCharacterBase::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APirateCharacterBase::SemiLockedLook(const FInputActionValue& Value)
{
	TObjectPtr<AShipControllPart> ShipPart = Cast<AShipControllPart>(InteractionComponent->CurrentlyInteractedActor);
	if (ShipPart)
	{
		ShipPart->Look(Value);
	}
}

//void APirateCharacterBase::TurnWheel(const FInputActionValue& Value)
//{
//	TObjectPtr<AShipControllPart> Wheele = Cast<AShipControllPart>(InteractionComponent->CurrentlyInteractedActor);
//	if (Wheele)
//	{
//		Wheele->AddControllValue(Value.Get<float>());
//	}
//}
//
//void APirateCharacterBase::RaisSail(const FInputActionValue& Value)
//{
//	TObjectPtr<AShipControllPart> Sail = Cast<AShipControllPart>(InteractionComponent->CurrentlyInteractedActor);
//	if (Sail)
//	{
//		Sail->AddControllValue(Value.Get<float>());
//	}
//}

void APirateCharacterBase::AddShipControllPartValue(const FInputActionValue& Value)
{
	TObjectPtr<AShipControllPart> ShipControllPart = Cast<AShipControllPart>(InteractionComponent->CurrentlyInteractedActor);
	if (ShipControllPart)
	{
		ShipControllPart->AddControllValue(Value.Get<float>());
	}
}

void APirateCharacterBase::Interact(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Interacting"));
	InteractionComponent->PrimaryInteract();
}
