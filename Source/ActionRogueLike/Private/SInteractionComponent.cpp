// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"


// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector EyeLocation;
	FRotator EyeRotation;

	AActor* Owner = GetOwner();
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000.f);
	TArray<FHitResult> Hits;

	FColor LineColor = FColor::Red;
	float Radius = 30.f;
	//GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);
	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	if (GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape))
	{
		for (FHitResult HitResult : Hits)
		{
			if (AActor* HitActor = HitResult.GetActor())
			{
				if (HitActor->Implements<USGameplayInterface>())
				{
					if (APawn* MyPawn = Cast<APawn>(Owner))
					{
						ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
						LineColor = FColor::Green;
					}
				}
			}
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, Radius, 32, LineColor, false, 2.f);
		}
	}
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.f, 0.f, 2.f);
}

// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
