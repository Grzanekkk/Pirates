// Made by Jan Puto 2023 :>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PirateCharacterBase.generated.h"

class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class UPirateInteractionComponent;
enum class EPirateCharacterState : uint8;

UCLASS()
class PIRATES_API APirateCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APirateCharacterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerState(EPirateCharacterState NewPlayerCharacterState);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	EPirateCharacterState PlayerCharacterState;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pirates|Components")
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pirates|Components")
	TObjectPtr<UPirateInteractionComponent> InteractionComponent;

	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pirates|Interaction")
	//TObjectPtr<AActor> CurrentlyInteractedObject;

#pragma region Input

protected:

	void SetPlayerActionsBasedOnState();

	void LockCamera();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for looking during using a wheel or adjusting sails*/
	void SemiLockedLook(const FInputActionValue& Value);

	/** Called for turning wheel input */
	void TurnWheel(const FInputActionValue& Value);

	/** Called for raising sail input */
	void RaisSail(const FInputActionValue& Value);

	/** Called for interaction input */
	void Interact(const FInputActionValue& Value);

	/** MappingContext */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Input")
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Input")
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Input")
	TObjectPtr<UInputAction> TurnWheelAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Input")
	TObjectPtr<UInputAction> InteractAction;

#pragma endregion 



};
