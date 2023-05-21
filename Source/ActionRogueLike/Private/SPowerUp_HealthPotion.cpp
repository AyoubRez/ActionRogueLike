// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUp_HealthPotion.h"

#include "SAttributesComponent.h"


ASPowerUp_HealthPotion::ASPowerUp_HealthPotion(): Healing(25.f)
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
}

void ASPowerUp_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))return;
	USAttributesComponent* AttributesComponent = Cast<USAttributesComponent>(
		InstigatorPawn->GetComponentByClass(USAttributesComponent::StaticClass()));

	if (ensure(AttributesComponent) && !AttributesComponent->IsFullHealth())
	{
		if (AttributesComponent->ApplyHealthChange(FMath::Floor(Healing * AttributesComponent->GetMaxHealth() / 100)))
		{
			HideAndCooldownPowerUp();
		}
	}
}
