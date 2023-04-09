// Made by Jan Puto 2023 :>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pirates/Interfaces/PirateInteractionInterface.h"
#include "ShipControllPart.generated.h"

class UCameraComponent;
class UBoxComponent;
class UArrowComponent;
class APirateCharacterBase;
enum class EPirateCharacterState : uint8;

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

	UFUNCTION()
	void OnCameraBlendInFinished();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Settings")
	float ControllMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Settings")
	float ControllMinBounds = -100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Settings")
	float ControllMaxBounds = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Settings")
	float CameraBlendInTime = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Settings")
	float CameraBlendOutTime = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Settings")
	EPirateCharacterState PirateCharacterStateWhenControlling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pirates|Data")
	bool bIsPlayerUsingControllPart = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pirates|Data")
	TObjectPtr<APirateCharacterBase> ControllingPirateCharacter;

	UPROPERTY()
	FTimerHandle CameraBlendInTimer;


#pragma region Components

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Components")
	TObjectPtr<UArrowComponent> RootArrowComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Components")
	TObjectPtr<UStaticMeshComponent> MainMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Components")
	TObjectPtr<UCameraComponent> ControllPartCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Components")
	TObjectPtr<UArrowComponent> PlayerLocationPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Components")
	TObjectPtr<UArrowComponent> InteractionWidgetLocationPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Components")
	TObjectPtr<UBoxComponent> InteractionAreaBoxComponent;

#pragma endregion 

#pragma region InteractionInterface

	virtual void Interact_Implementation(APawn* Instigator) override;

	virtual bool CanInteract_Implementation(APawn* Instigator) override;

	virtual void UnInteract_Implementation(APawn* Instigator) override;

	virtual bool CanUnInteract_Implementation(APawn* Instigator) override;

	virtual bool IsEnabled_Implementation() override;

	virtual bool CanShowInteractionWidget_Implementation(APawn* Instigator) override;

	virtual FVector GetInteractionWidgetLocation_Implementation() override;


#pragma endregion 
};
