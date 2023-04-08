// Made by Jan Puto 2023 :>


#include "Pirates/UI/WorldUserWidget.h"
#include "Pirates/Interfaces/PirateInteractionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"

void UWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsValid(AttachedActor))
	{
		RemoveFromParent();

		//FString Msg = FString::Printf(TEXT("AttachedActor is no longer valid. Removing %s widget from viewport"), *this->GetName());
		//ULogsFunctionLibrary::LogOnScreen(GetWorld(), Msg, ERogueLogCategory::WARNING);

		return;
	}

	FVector2D OnScreenPosition;
	if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), IPirateInteractionInterface::Execute_GetInteractionWidgetLocation(AttachedActor), OnScreenPosition))
	{
		//Returns false if coundnot find position on the screen

		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

		OnScreenPosition /= Scale;

		if (ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(OnScreenPosition);
		}
	}
}