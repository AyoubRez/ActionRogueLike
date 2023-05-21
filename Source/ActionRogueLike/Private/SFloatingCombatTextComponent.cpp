// Fill out your copyright notice in the Description page of Project Settings.


#include "SFloatingCombatTextComponent.h"

#include "SFloatingTextActor.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/UserInterfaceSettings.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USFloatingCombatTextComponent::USFloatingCombatTextComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USFloatingCombatTextComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void USFloatingCombatTextComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	/*if (APawn* Pawn = CastChecked<APawn>(GetOwner()))
	{
		if (Pawn != nullptr && Pawn->IsLocallyControlled() == false)return;
		const FVector2D ViewPortSize = UWidgetLayoutLibrary::GetViewportSize(this);
		if (ViewPortSize.X <= 0.f || ViewPortSize.Y <= 0.f)return;
		const int32 ViewPortX = FGenericPlatformMath::FloorToInt32(ViewPortSize.X);
		const int32 ViewPortY = FGenericPlatformMath::FloorToInt32(ViewPortSize.Y);
		const float ViewPortScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->
			GetDPIScaleBasedOnSize(
				FIntPoint(ViewPortX, ViewPortY));
		if (ViewPortScale <= 0.f)return;

		const FVector CameraLocation = GetOwner<APawn>()->GetController<APlayerController>()->PlayerCameraManager->
		                                                  GetCameraLocation();
		int32 i = 0;
		for (ASFloatingTextActor* ActiveText : ActiveTextActors)
		{
			if (i > 0)
			{
				const float Distance = FVector::Dist(CameraLocation, ActiveText->GetAnchorLocation());
				const float VerticalOffset = Distance / (ViewPortSize.X / ViewPortScale);

				ActiveText->SetActorLocation(
					ActiveText->GetAnchorLocation() + FVector(0.f, 0.f, i * VerticalOffset * TextVerticalSpacing));
			}
			i++;
		}
	}*/
}


void USFloatingCombatTextComponent::AddFloatingText_Client_Implementation(const FText& Text, FVector WorldLocation)
{
	if (FloatingTextActorClass == nullptr)return;
	const FTransform SpawnTransform = FTransform(FRotator::ZeroRotator,
	                                             WorldLocation + FVector(0.f, 0.f, TextVerticalOffset));
	ASFloatingTextActor* NewTextActor = GetWorld()->SpawnActorDeferred<ASFloatingTextActor>(
		FloatingTextActorClass, SpawnTransform, GetOwner());
	if (NewTextActor == nullptr)return;
	NewTextActor->Initialize(Text);
	NewTextActor->OnDestroyed.AddDynamic(this, &USFloatingCombatTextComponent::OnTextDestroyed);
	UGameplayStatics::FinishSpawningActor(NewTextActor, SpawnTransform);
	ActiveTextActors.Insert(NewTextActor, 0);
}


void USFloatingCombatTextComponent::OnTextDestroyed(AActor* DestroyedActor)
{
	ActiveTextActors.Pop();
}
