// Made by Jan Puto 2023 :>

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PirateInteractionComponent.generated.h"

class UWorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIRATES_API UPirateInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPirateInteractionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void PrimaryInteract();

	UFUNCTION(Server, Reliable)
	void ServerPrimaryInteract(AActor* InFocusedActor);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Interaction")
	TObjectPtr<AActor> CurrentlyInteractedActor = nullptr;

protected:
	UFUNCTION()
	void FindBestInteractable();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Interaction")
	TObjectPtr<AActor> FocusedActor = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Interaction|UI")
	TSubclassOf<UWorldUserWidget> DefaultWidgetClass = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Interaction|UI")
	TObjectPtr<UWorldUserWidget> WidgetInstance = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Interaction|Trace")
	float InteractionDistance = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Interaction|Trace")
	float InteractionRadius = 30.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pirates|Interaction|Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel = ECC_WorldDynamic;
};
