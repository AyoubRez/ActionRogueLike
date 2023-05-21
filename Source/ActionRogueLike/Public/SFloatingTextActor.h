// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFloatingTextActor.generated.h"

UCLASS(Abstract)
class ACTIONROGUELIKE_API ASFloatingTextActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASFloatingTextActor();
	const FVector& GetAnchorLocation() const { return AnchorLocation; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent, Category="FloatingText")
	void Initialize(const FText& Text);

private:
	FVector AnchorLocation;
};
