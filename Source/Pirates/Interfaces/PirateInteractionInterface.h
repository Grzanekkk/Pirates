// Made by Jan Puto 2023 :>

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PirateInteractionInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPirateInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class PIRATES_API IPirateInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pirates|Interaction")
	void Interact(APawn* Instigator);

	// Here we are checking if player meets requierements to interact fe: has enough coins or is damaged
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pirates|Interaction")
	bool CanInteract(APawn* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pirates|Interaction")
	void UnInteract(APawn* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pirates|Interaction")
	bool CanUnInteract(APawn* Instigator);

	// Here we are checking if interactable object itself is capable of beeing interacted fe: is not on cooldown
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pirates|Interaction")
	bool IsEnabled();

	// If set to false this interactable can only be interacted by non player objects fe: levers, zones
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pirates|Interaction")
	bool CanShowInteractionWidget(APawn* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Pirates|Interaction")
	FVector GetInteractionWidgetLocation();
};
