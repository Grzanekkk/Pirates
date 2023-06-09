// Made by Jan Puto 2023 :>


#include "Pirates/Components/PirateInteractionComponent.h"
#include "Pirates/UI/WorldUserWidget.h"
#include "Pirates/Interfaces/PirateInteractionInterface.h"

static TAutoConsoleVariable<bool> CVarDrawInteractionDebug(TEXT("jp.DrawInteractionDebug"), false, TEXT("Draw Debug Shapes for Interaction Component."), ECVF_Cheat);


UPirateInteractionComponent::UPirateInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPirateInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn->IsLocallyControlled())
	{
		FindBestInteractable();
	}
}

void UPirateInteractionComponent::FindBestInteractable()
{
	bool bDrawDebug = CVarDrawInteractionDebug.GetValueOnGameThread();

	AActor* Owner = GetOwner();
	if (Owner == nullptr || Owner->GetInstigatorController() == nullptr)
	{
		return;
	}

	FVector TraceStart = FVector::ZeroVector;
	FRotator EyeRotation;
	Owner->GetInstigatorController()->GetPlayerViewPoint(TraceStart, EyeRotation);
	FVector ShotDirection = EyeRotation.Vector();
	FVector TraceEnd = TraceStart + ShotDirection * InteractionDistance;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

	TArray<FHitResult> Hits;
	FCollisionShape SweepShape;
	SweepShape.SetSphere(InteractionRadius);

	bool bHitSuccess = GetWorld()->SweepMultiByObjectType(Hits, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, SweepShape);
	FColor LineColor = bHitSuccess ? FColor::Green : FColor::Red;

	// Clear ref
	FocusedActor = nullptr;
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	for (FHitResult Hit : Hits)
	{
		if (bDrawDebug)
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactNormal, InteractionRadius, 32, LineColor, false, 0.f);
		}

		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UPirateInteractionInterface>() && IPirateInteractionInterface::Execute_IsEnabled(HitActor) && IPirateInteractionInterface::Execute_CanShowInteractionWidget(HitActor, OwnerPawn))
			{
				FocusedActor = HitActor;
				break;
			}
		}
	}

	if (FocusedActor)
	{
		if (WidgetInstance == nullptr && ensure(DefaultWidgetClass))
		{
			WidgetInstance = CreateWidget<UWorldUserWidget>(GetWorld(), DefaultWidgetClass);
		}

		if (WidgetInstance)
		{
			WidgetInstance->AttachedActor = FocusedActor;

			if (!WidgetInstance->IsInViewport())
			{
				WidgetInstance->AddToViewport();
			}
		}
	}
	else
	{
		if (WidgetInstance)
		{
			WidgetInstance->RemoveFromParent();
		}
	}

	if (bDrawDebug)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, LineColor, false, 2, 0, 0);
	}
}

void UPirateInteractionComponent::PrimaryInteract()
{
	ServerPrimaryInteract(FocusedActor);
}

void UPirateInteractionComponent::ServerPrimaryInteract_Implementation(AActor* InFocusedActor)
{
	if (!CurrentlyInteractedActor)
	{
		if (InFocusedActor == nullptr)
		{
			//ULogsFunctionLibrary::LogOnScreen(GetWorld(), "No Focused Actreo to Interact.", ERogueLogCategory::WARNING);
			return;
		}

		APawn* OwnerPawn = Cast<APawn>(GetOwner());

		if (IPirateInteractionInterface::Execute_CanInteract(InFocusedActor, OwnerPawn))
		{
			IPirateInteractionInterface::Execute_Interact(InFocusedActor, OwnerPawn);

			CurrentlyInteractedActor = InFocusedActor;
			return;
		}

		CurrentlyInteractedActor = nullptr;
		return;
	}
	else
	{
		// If we are currenty interacting with something we are going to un-interact it
		APawn* OwnerPawn = Cast<APawn>(GetOwner());

		if (IPirateInteractionInterface::Execute_CanUnInteract(CurrentlyInteractedActor, OwnerPawn))
		{
			IPirateInteractionInterface::Execute_UnInteract(CurrentlyInteractedActor, OwnerPawn);

			CurrentlyInteractedActor = nullptr;
			return;
		}
	}
}

