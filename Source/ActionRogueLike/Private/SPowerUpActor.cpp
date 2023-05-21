// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpActor.h"

#include "Components/SphereComponent.h"

ASPowerUpActor::ASPowerUpActor(): RespawnTime(10.f)
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName("PowerUp");
	SetRootComponent(SphereComp);
}

void ASPowerUpActor::ShowPowerUp()
{
	SetPowerUpState(true);
}

void ASPowerUpActor::HideAndCooldownPowerUp()
{
	SetPowerUpState(false);
	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ASPowerUpActor::ShowPowerUp, RespawnTime);
}

void ASPowerUpActor::SetPowerUpState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);
	RootComponent->SetVisibility(bNewIsActive, true);
}

void ASPowerUpActor::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);
}
