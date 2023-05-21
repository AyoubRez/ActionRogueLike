// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API ASExplosiveBarrel : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

public:
	ASExplosiveBarrel();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;

	virtual void BeginPlay() override;
	
	void Explode();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	           const FHitResult& Hit);

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	virtual void PostInitializeComponents() override;

public:
	virtual void Tick(float DeltaTime) override;
};
