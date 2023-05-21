// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SFloatingCombatTextComponent.generated.h"


class ASFloatingTextActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API USFloatingCombatTextComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FLoatingText", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ASFloatingTextActor> FloatingTextActorClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FLoatingText", meta=(AllowPrivateAccess="true"))
	float TextVerticalSpacing = 40.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FLoatingText", meta=(AllowPrivateAccess="true"))
	float TextVerticalOffset = 100.f;

public:
	// Sets default values for this component's properties
	USFloatingCombatTextComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Client, Unreliable, BlueprintCallable, Category="FloatingCombatTextComponent")
	void AddFloatingText_Client(const FText& Text, FVector WorldLocation);

private:
	UFUNCTION()
	void OnTextDestroyed(AActor* DestroyedActor);

	UPROPERTY()
	TArray<ASFloatingTextActor*> ActiveTextActors;
};
