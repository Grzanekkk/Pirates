// Made by Jan Puto 2023 :>

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorldUserWidget.generated.h"

class USizeBox;

/**
 * 
 */
UCLASS()
class PIRATES_API UWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pirates|UI", meta = (ExposeOnSpawn = true))
	TObjectPtr<AActor> AttachedActor;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pirates|UI")
	//FVector WorldOffset;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> ParentSizeBox;

};
