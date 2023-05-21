// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributesComponent.h"


USAttributesComponent::USAttributesComponent(): MaxHealth(500.f)
{
	Health = MaxHealth;
}

bool USAttributesComponent::IsAlive() const
{
	return Health > 0;
}

bool USAttributesComponent::IsFullHealth() const
{
	return Health >= MaxHealth;
}

bool USAttributesComponent::ApplyHealthChange(float Delta)
{
	const float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.f, MaxHealth);
	const float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(GetOwner(), this, Health, ActualDelta);
	return ActualDelta != 0.f;
}
